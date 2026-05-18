#!/usr/bin/env python3

import sys
import streamlit as st

proj_dir = __file__[:__file__.lower().rfind("bioevo") + len("bioevo")]
if proj_dir not in sys.path:
    sys.path = [proj_dir] + sys.path

from apps.sandbox.backend import BE


def run():
    st.set_page_config(page_title="EvoX Sandbox", layout="wide")
    st.title("EvoX Inspector")

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


if __name__ == "__main__":
    
    run()

# streamlit run apps/sandbox/sandbox.py --server.headless=true
