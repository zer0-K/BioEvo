#!/usr/bin/env python3

import sys
import streamlit as st

proj_dir = __file__[:__file__.lower().rfind("bioevo") + len("bioevo")]
if proj_dir not in sys.path:
    sys.path = [proj_dir] + sys.path

from apps.sandbox.backend import BE


# ── page: inspector ──────────────────────────────────────────────────────────

def page_inspector():
    with st.sidebar:
        st.header("Files")
        uploads = st.file_uploader(
            "Load .evox or .csv file(s)",
            type=["evox", "csv"],
            accept_multiple_files=True,
        )
        st.caption("One file → inspect.  Two files → inspect + diff.")
        st.divider()
        show_ref = st.checkbox("Show tRNA reference table")

    if show_ref:
        with st.expander("tRNA reference", expanded=True):
            BE.OTHER.show_trna_reference()

    if not uploads:
        st.info("Load one or two .evox / .csv files from the sidebar to get started.")
        st.stop()

    bodies = [BE.PARSING.load_file(f) for f in uploads]

    if len(bodies) == 1:
        b = bodies[0]
        st.subheader(b.source)
        BE.DISP_HELP.show_body(b)
    else:
        b1, b2 = bodies[0], bodies[1]
        col1, col2 = st.columns(2)
        with col1:
            st.subheader(b1.source)
            BE.DISP_HELP.show_body(b1)
        with col2:
            st.subheader(b2.source)
            BE.DISP_HELP.show_body(b2)
        st.divider()
        BE.DIFF.show_diff(b1, b2)


# ── page: builder ─────────────────────────────────────────────────────────────

def page_builder():
    st.subheader("Universe Builder")

    if "config" not in st.session_state:
        st.session_state.config = BE.EXPERIMENT.Config()
    config = st.session_state.config

    # Load existing experiment from sidebar
    with st.sidebar:
        st.header("Load saved experiment")
        load_dir = st.text_input("Directory", key="builder_load_dir",
                                 placeholder="data/experiments/my_exp")
        if st.button("Load") and load_dir:
            try:
                st.session_state.config = BE.EXPERIMENT.load(load_dir)
                st.session_state.experiment_dir = load_dir
                st.success(f"Loaded from {load_dir}")
                st.rerun()
            except Exception as e:
                st.error(str(e))

    # ── run parameters ───────────────────────────────────────────────────────
    st.markdown("#### Parameters")
    col1, col2, col3, col4 = st.columns(4)
    config.name              = col1.text_input("Name", value=config.name)
    config.nb_steps          = col2.number_input("Steps", min_value=1,
                                                  value=config.nb_steps, step=1)
    config.max_nb_instr_exec = col3.number_input("Max instr / exec",
                                                  value=config.max_nb_instr_exec, step=1_000_000)
    config.data_stack_init   = col4.number_input("Data stack init (pos 99)",
                                                  value=config.data_stack_init, step=1)

    # ── cells ────────────────────────────────────────────────────────────────
    st.divider()
    st.markdown("#### Cells")
    current_n = max(config.cells.keys()) + 1 if config.cells else 1
    nb_cells = st.number_input("Number of cells", min_value=1, max_value=20,
                                value=current_n, step=1)

    for i in range(nb_cells):
        with st.expander(f"Cell {i}", expanded=True):
            mode = st.radio("Type", ["EvoX", "Void"], key=f"cell_mode_{i}", horizontal=True,
                            index=0 if config.cells.get(i) is not None else 1)

            if mode == "Void":
                config.cells[i] = None
            else:
                uploaded = st.file_uploader("Load .evox file", type=["evox"],
                                             key=f"cell_upload_{i}")
                if uploaded:
                    config.cells[i] = uploaded.read().decode("utf-8")

                # Show paste area only when no file has been loaded yet
                if not config.cells.get(i):
                    pasted = st.text_area("…or paste .evox content",
                                          height=80, key=f"cell_paste_{i}")
                    if pasted.strip():
                        config.cells[i] = pasted

                # Preview
                body_text = config.cells.get(i)
                if body_text:
                    parsed = BE.PARSING.parse_evox(body_text, f"cell {i}")
                    if parsed.error:
                        st.error(parsed.error)
                    else:
                        st.caption(
                            f"{len(parsed.progteins)} progteins · "
                            f"{len(parsed.genes)} genes · "
                            f"{len(parsed.raw_rows)} RAW rows"
                        )
                else:
                    st.caption("No body loaded.")

    # ── save ─────────────────────────────────────────────────────────────────
    st.divider()
    save_dir = st.text_input(
        "Save experiment to directory",
        value=st.session_state.get("experiment_dir", "data/experiments/sandbox_exp"),
        key="builder_save_dir",
    )
    if st.button("Save experiment", type="primary"):
        try:
            BE.EXPERIMENT.save(config, save_dir)
            st.session_state.experiment_dir = save_dir
            st.success(f"Saved to {save_dir}")
        except Exception as e:
            st.error(str(e))


# ── page: run ────────────────────────────────────────────────────────────────

def page_run():
    st.subheader("Run")

    if "config" not in st.session_state:
        st.warning("Go to **Builder** first to set up a universe, or load one from a directory.")
        return

    config = st.session_state.config

    with st.sidebar:
        st.header("Run settings")
        binary = st.text_input("sandbox-runner binary",
                                value=BE.EXPERIMENT.default_binary())
        exp_dir = st.text_input(
            "Experiment directory",
            value=st.session_state.get("experiment_dir", "data/experiments/sandbox_exp"),
            key="run_exp_dir",
        )

    # Summary of the current config
    cell_summary = {str(k): ("evox" if v else "void") for k, v in config.cells.items()}
    st.json({
        "name":              config.name or "(unnamed)",
        "nb_steps":          config.nb_steps,
        "max_nb_instr_exec": config.max_nb_instr_exec,
        "data_stack_init":   config.data_stack_init,
        "cells":             cell_summary,
    })

    if st.button("Run", type="primary"):
        with st.spinner(f"Running {config.nb_steps} step(s)…"):
            try:
                result = BE.EXPERIMENT.run(config, exp_dir, binary)
                st.session_state.experiment_dir = exp_dir
                if result.returncode == 0:
                    st.success("Simulation complete.")
                    st.session_state.timeline = BE.EXPERIMENT.read_timeline(exp_dir)
                    if result.stdout:
                        st.text(result.stdout)
                else:
                    st.error("Runner exited with an error.")
                    if result.stderr:
                        st.text(result.stderr)
                    if result.stdout:
                        st.text(result.stdout)
            except FileNotFoundError:
                st.error(
                    f"Binary not found: `{binary}`\n\n"
                    "Build it first with:\n```\ncmake --build build --target sandbox-runner\n```"
                )
            except Exception as e:
                st.error(str(e))

    # If we already have timeline results, offer a quick link
    if "timeline" in st.session_state and st.session_state.timeline:
        st.info(f"Timeline loaded ({len(st.session_state.timeline)} steps). "
                "Go to **Timeline** to explore it.")


# ── page: timeline ────────────────────────────────────────────────────────────

def page_timeline():
    st.subheader("Timeline")

    with st.sidebar:
        st.header("Load timeline")
        tl_dir = st.text_input(
            "Experiment directory",
            value=st.session_state.get("experiment_dir", ""),
            key="tl_dir",
        )
        if st.button("Load timeline") and tl_dir:
            try:
                st.session_state.timeline = BE.EXPERIMENT.read_timeline(tl_dir)
                st.session_state.experiment_dir = tl_dir
                st.success(f"Loaded {len(st.session_state.timeline)} steps.")
            except Exception as e:
                st.error(str(e))

    timeline = st.session_state.get("timeline")
    if not timeline:
        st.info("Run a simulation (Run page) or load an existing experiment directory.")
        return

    BE.DISP_HELP.show_timeline(timeline)


# ── entry point ───────────────────────────────────────────────────────────────

def run():
    st.set_page_config(page_title="EvoX Sandbox", layout="wide")
    st.title("EvoX Sandbox")

    page = st.sidebar.radio(
        "Navigation",
        ["Inspector", "Builder", "Run", "Timeline"],
        index=0,
    )

    if page == "Inspector":
        page_inspector()
    elif page == "Builder":
        page_builder()
    elif page == "Run":
        page_run()
    elif page == "Timeline":
        page_timeline()


if __name__ == "__main__":
    run()

# streamlit run apps/sandbox/sandbox.py --server.headless=true
