#!/usr/bin/env python3
"""
Backend of the sandbox app
"""

import re
import difflib
from dataclasses import dataclass, field
from pathlib import Path
import pandas
import streamlit as st


class BE:
    
    class CST:

        SIZE_INSTR = 7
        GSTART_ID  = -51451
        GSTOP_ID   = -77142

        OPCODES = {
            0: "XXX", 1: "MOV", 2: "CPY", 3: "CPYIN", 4: "CPYOUT", 5: "INC", 6: "DEC",
            7: "ADD", 8: "SUB", 9: "MUL", 10: "DIV", 11: "OPP", 12: "CPYIS", 13: "SETOS",
            14: "CPYUS", 15: "EMPTY", 16: "READ", 17: "WRITE", 18: "CMP",
            19: "JMP", 20: "JRA", 21: "JRS", 22: "JE", 23: "JL", 24: "JG",
            25: "JLE", 26: "JGE", 27: "JRE", 28: "JRL", 29: "JRG", 30: "JRLE", 31: "JRGE",
            32: "GPTR", 33: "BEG", 34: "HALT", 35: "RUD", 36: "RUI", 37: "RN", 38: "RG",
            39: "GR", 40: "GINS", 41: "GDEL", 42: "GDELW", 43: "GSET", 44: "GADD",
            45: "GCPY", 46: "MARKER", 47: "GCPYM", 48: "EXEC", 49: "CALL", 50: "REGEN",
        }

        # id → (short_name, arity)
        TRNA = {
            9999:  ("RET",        0), 10000: ("CVARS",      2), 10001: ("IVARS",      0),
            10100: ("SLVcst",     2), 10101: ("SDLVcst",    2), 10110: ("SLVLV",      2),
            10111: ("SDLVLV",     2), 10112: ("SLVDLV",     2), 10113: ("SDLVDLV",    2),
            10114: ("ScstLV",     2), 10115: ("SLVaddr",    2),
            10150: ("RGLVLV",     2), 10170: ("WGDLV",      3),
            10200: ("GILV",       2), 10201: ("GDILV",      2), 10202: ("GIDLV",      2),
            10203: ("GDIDLV",     2), 10210: ("GTSLV",      1), 10211: ("GTSLVD",     1),
            10212: ("GTSDLV",     1), 10250: ("GLVO",       2),
            10500: ("IF0",        1), 10600: ("SIJ",        0), 10700: ("SEJ",        0),
            10800: ("SWJ",        1), 10900: ("JLV",        1),
            11000: ("SOScst",     1), 11001: ("SOSLV",      1), 11010: ("GISLV",      1),
            11100: ("PCSI",       1), 11150: ("PLVSI",      1), 11200: ("PCSWI",      1),
            11250: ("PLVSWI",     1), 11300: ("CMPLVcst",   4), 11350: ("CMPLVLV",    4),
            11400: ("OPEcstcst",  3), 11401: ("OPEcstLV",   3), 11402: ("OPELVcst",   3),
            11403: ("OPELVLV",    3), 11450: ("INCcst",     2), 11451: ("INCLV",      2),
            11452: ("INCDLV",     2), 11453: ("INCS",       1), 11500: ("CALLcst",    1),
            11501: ("CALLLV",     1), 11600: ("RUIcstcst",  3), 11601: ("RUIcstLV",   3),
            11602: ("RUILVcst",   3), 11603: ("RUILVLV",    3), 12000: ("GScstcst",   2),
            12001: ("GScstLV",    2), 12002: ("GSLVcst",    2), 12003: ("GSLVLV",     2),
            12500: ("GADD",       2), 13000: ("USLV",       1), 13001: ("RULV",       1),
            13100: ("EMPTY",      2), 13200: ("WRITE",      2), 14999: ("HALT",       0),
            14000: ("MP",         0), 14010: ("ME",         0), 14100: ("Mcst",       1),
            14101: ("M0",         0), 14102: ("M1",         0), 14103: ("M2",         0),
            14104: ("M3",         0), 14200: ("MInstr",     1), 14201: ("MCPY",       0),
            14300: ("Marg",       0), 14301: ("MargW",      0), 14310: ("MLV",        0),
            14311: ("MLVW",       0), 15000: ("SP_GPTR",    0), 15001: ("SP_FCTADD",  0),
            15002: ("SP_GFPTRLV", 1), 15003: ("SP_GSPLV",   1), 15004: ("SP_GCPY",    3),
        }

    class MODEL:

        @dataclass
        class Progtein:
            id: int
            name: str = ""
            instructions: list = field(default_factory=list)  # list[str]

        @dataclass
        class Gene:
            id: int
            tokens: list = field(default_factory=list)  # list[str]

        @dataclass
        class ParsedBody:
            raw_rows:   list = field(default_factory=list)   # list[list[int]]
            progteins:  list = field(default_factory=list)   # list[Progtein]
            genes:      list = field(default_factory=list)   # list[Gene]
            trail_rows: list = field(default_factory=list)   # list[list[int]]
            source:     str  = ""
            error:      str  = ""

    class PARSING:

        def _strip_comment(line: str) -> str:
            idx = line.find("//")
            return line[:idx] if idx >= 0 else line

        def parse_evox(text: str, source: str = "") -> ParsedBody:
            """Parse .evox text format."""
            b = BE.MODEL.ParsedBody(source=source)
            lines = text.splitlines()
            i = 0

            while i < len(lines):
                line = BE.PARSING._strip_comment(lines[i]).strip()
                i += 1
                if not line:
                    continue
                kw = line.split()[0].upper()

                if kw == "RAW":
                    while i < len(lines):
                        l = BE.PARSING._strip_comment(lines[i]).strip(); i += 1
                        if not l: continue
                        if l.upper() == "END": break
                        b.raw_rows.append([int(x) for x in l.split()])

                elif kw == "PROGTEIN":
                    parts = line.split()
                    p = BE.MODEL.Progtein(id=0)
                    for tok in parts[1:]:
                        if tok.startswith("id="):
                            p.id = int(tok[3:])
                        elif re.match(r"^-?\d+$", tok):
                            p.id = int(tok)
                        else:
                            p.name = tok
                    while i < len(lines):
                        l = BE.PARSING._strip_comment(lines[i]).strip(); i += 1
                        if not l: continue
                        if l.upper() == "END": break
                        p.instructions.append(l)
                    b.progteins.append(p)

                elif kw == "DNA":
                    current_gene = None
                    while i < len(lines):
                        l = BE.PARSING._strip_comment(lines[i]).strip(); i += 1
                        if not l: continue
                        kw2 = l.split()[0].upper()
                        if kw2 == "END":
                            if current_gene is not None:
                                b.genes.append(current_gene)
                                current_gene = None
                            else:
                                break
                        elif kw2 == "GENE":
                            m = re.search(r"id=(-?\d+)", l)
                            current_gene = BE.MODEL.Gene(id=int(m.group(1)) if m else 0)
                        elif kw2 == "PAD":
                            pass
                        elif current_gene is not None:
                            current_gene.tokens.append(l)

                elif kw == "TRAIL":
                    while i < len(lines):
                        l = BE.PARSING._strip_comment(lines[i]).strip(); i += 1
                        if not l: continue
                        if l.upper() == "END": break
                        b.trail_rows.append([int(x) for x in l.split()])

            return b

        def _fmt_dna_content(flat: list[int]) -> list[str]:
            """Convert flat int list (gene content) to tRNA token strings."""
            lines = []
            j = 0
            while j < len(flat):
                tok = flat[j]
                info = BE.CST.TRNA.get(tok)
                if info:
                    name, arity = info
                    args = flat[j + 1 : j + 1 + arity]
                    line = name + (" " + " ".join(str(a) for a in args) if args else "")
                    lines.append(line)
                    j += 1 + arity
                else:
                    lines.append(str(tok))
                    j += 1
            return lines

        def parse_csv(text: str, source: str = "") -> ParsedBody:
            """Parse flat int CSV format (one molecule per line, 7 comma-separated ints)."""
            molecules = []
            for line in text.splitlines():
                line = line.strip().rstrip(",")
                if not line:
                    continue
                try:
                    vals = [int(x.strip()) for x in line.split(",")]
                    if len(vals) == BE.CST.SIZE_INSTR:
                        molecules.append(vals)
                except ValueError:
                    pass

            if not molecules:
                b = BE.MODEL.ParsedBody(source=source)
                b.error = "No valid molecules found (expected 7-int rows)."
                return b

            return BE.PARSING._molecules_to_body(molecules, source)

        def _molecules_to_body(mols: list, source: str) -> ParsedBody:
            """Convert list of SIZE_INSTR-int molecules to ParsedBody."""
            b = BE.MODEL.ParsedBody(source=source)
            n = len(mols)

            def opcode_name(code):
                return BE.CST.OPCODES.get(code, str(code))

            def mol_str(m):
                return opcode_name(m[0]) + " " + " ".join(str(x) for x in m[1:])

            # Locate DNA markers: {46, 0, -1, ...}
            dna_start = dna_end = -1
            for i, m in enumerate(mols):
                if m[0] == 46 and m[1] == 0 and m[2] == -1:
                    if dna_start < 0:
                        dna_start = i
                    else:
                        dna_end = i
                        break

            prog_end    = dna_start if dna_start >= 0 else n
            trail_start = dna_end + 1 if dna_end >= 0 else n

            # RAW: molecules before first MARKER
            cur = 0
            while cur < prog_end and mols[cur][0] != 46:
                b.raw_rows.append(mols[cur])
                cur += 1

            # Progteins
            while cur < prog_end:
                m = mols[cur]
                if m[0] != 46:
                    cur += 1
                    continue
                pid = m[2]
                trna_info = BE.MODEL.TRNA.get(pid)
                p = BE.MODEL.Progtein(id=pid, name=trna_info[0] if trna_info else "")
                cur += 1
                while cur < prog_end:
                    cm = mols[cur]; cur += 1
                    p.instructions.append(mol_str(cm))
                    if cm[0] == 46 and cm[2] == pid:
                        break
                b.progteins.append(p)

            # DNA: flatten molecules between markers, parse genes
            if dna_start >= 0 and dna_end >= 0:
                flat = [v for m in mols[dna_start + 1 : dna_end] for v in m]
                j = 0
                while j < len(flat):
                    if flat[j] != BE.CST.GSTART_ID:
                        j += 1
                        continue
                    j += 1
                    if j >= len(flat):
                        break
                    gene_id = flat[j]; j += 1
                    content = []
                    while j < len(flat) and flat[j] != BE.CST.GSTOP_ID:
                        content.append(flat[j]); j += 1
                    if j < len(flat) and flat[j] == BE.CST.GSTOP_ID:
                        j += 1
                    while j < len(flat) and flat[j] == 0:
                        j += 1
                    b.genes.append(Gene(id=gene_id, tokens=_fmt_dna_content(content)))

            # Trail
            for m in mols[trail_start:]:
                b.trail_rows.append(m)

            return b

        def load_file(uploaded) -> ParsedBody:
            text = uploaded.read().decode("utf-8")
            name = uploaded.name
            if name.endswith(".csv"):
                return BE.PARSING.parse_csv(text, name)
            return BE.PARSING.parse_evox(text, name)

    class DISP_HELP:

        def _progtein_label(p: Progtein) -> str:
            parts = []
            if p.name:
                parts.append(p.name)
            parts.append(f"id={p.id}")
            return " · ".join(parts) + f"  ({len(p.instructions)} instr)"

        def show_body(body: ParsedBody):
            if body.error:
                st.error(body.error)
                return

            c1, c2, c3, c4 = st.columns(4)
            total_mols = len(body.raw_rows) + sum(1 + len(p.instructions) for p in body.progteins) \
                        + len(body.trail_rows)
            c1.metric("Total molecules (approx)", total_mols)
            c2.metric("Progteins", len(body.progteins))
            c3.metric("Genes", len(body.genes))
            c4.metric("RAW rows", len(body.raw_rows))

            tabs = st.tabs(["Progteins", "DNA / Genes", "RAW & Trail"])

            with tabs[0]:
                if not body.progteins:
                    st.info("No progteins found.")
                else:
                    # Summary table
                    rows = [{"id": p.id, "name": p.name, "instructions": len(p.instructions)}
                            for p in body.progteins]
                    st.dataframe(pandas.DataFrame(rows), use_container_width=True, hide_index=True)
                    st.divider()
                    for p in body.progteins:
                        with st.expander(BE.DISP_HELP._progtein_label(p)):
                            st.code("\n".join(p.instructions), language="text")

            with tabs[1]:
                if not body.genes:
                    st.info("No genes found.")
                else:
                    rows = [{"id": g.id, "tokens": len(g.tokens)} for g in body.genes]
                    st.dataframe(pandas.DataFrame(rows), use_container_width=True, hide_index=True)
                    st.divider()
                    for g in body.genes:
                        with st.expander(f"Gene id={g.id}  ({len(g.tokens)} tokens)"):
                            st.code("\n".join(g.tokens), language="text")

            with tabs[2]:
                if body.raw_rows:
                    st.subheader("RAW")
                    cols = ["instr", "d1", "d2", "d3", "a1", "a2", "a3"]
                    raw_df = pandas.DataFrame(body.raw_rows, columns=cols[:len(body.raw_rows[0])])
                    st.dataframe(raw_df, use_container_width=True, hide_index=True)
                if body.trail_rows:
                    st.subheader("Trail")
                    trail_df = pandas.DataFrame(body.trail_rows)
                    st.dataframe(trail_df, use_container_width=True, hide_index=True)

    class DIFF:
        def show_diff(b1: ParsedBody, b2: ParsedBody):
            st.subheader("Diff")

            def _diff_items(items1, items2, id_key, label_fn, content_fn):
                map1 = {id_key(x): x for x in items1}
                map2 = {id_key(x): x for x in items2}
                all_ids = sorted(set(map1) | set(map2), key=lambda x: (x is None, x))
                added = removed = changed = same = 0
                rows = []
                for k in all_ids:
                    if k in map1 and k not in map2:
                        rows.append(("removed", map1[k], None))
                        removed += 1
                    elif k not in map1 and k in map2:
                        rows.append(("added", None, map2[k]))
                        added += 1
                    elif content_fn(map1[k]) != content_fn(map2[k]):
                        rows.append(("changed", map1[k], map2[k]))
                        changed += 1
                    else:
                        same += 1
                return rows, added, removed, changed, same

            # Progteins
            st.markdown("#### Progteins")
            prog_rows, pa, pr, pc, ps = _diff_items(
                b1.progteins, b2.progteins,
                id_key=lambda p: p.id,
                label_fn=BE.DISP_HELP._progtein_label,
                content_fn=lambda p: p.instructions,
            )
            c1, c2, c3, c4 = st.columns(4)
            c1.metric("Added",   pa, delta=pa  if pa  else None, delta_color="normal")
            c2.metric("Removed", pr, delta=-pr if pr  else None, delta_color="inverse")
            c3.metric("Changed", pc)
            c4.metric("Unchanged", ps)

            for status, x1, x2 in prog_rows:
                if status == "removed":
                    with st.expander(f"REMOVED  {BE.DISP_HELP._progtein_label(x1)}", expanded=False):
                        st.code("\n".join(x1.instructions), language="text")
                elif status == "added":
                    with st.expander(f"ADDED  {BE.DISP_HELP._progtein_label(x2)}", expanded=False):
                        st.code("\n".join(x2.instructions), language="text")
                else:
                    with st.expander(f"CHANGED  {BE.DISP_HELP._progtein_label(x1)}", expanded=False):
                        diff = list(difflib.unified_diff(
                            x1.instructions, x2.instructions,
                            fromfile="before", tofile="after", lineterm=""))
                        st.code("\n".join(diff), language="diff")

            st.markdown("#### Genes")
            gene_rows, ga, gr, gc, gs = _diff_items(
                b1.genes, b2.genes,
                id_key=lambda g: g.id,
                label_fn=lambda g: f"Gene id={g.id}",
                content_fn=lambda g: g.tokens,
            )
            c1, c2, c3, c4 = st.columns(4)
            c1.metric("Added",   ga, delta=ga  if ga  else None, delta_color="normal")
            c2.metric("Removed", gr, delta=-gr if gr  else None, delta_color="inverse")
            c3.metric("Changed", gc)
            c4.metric("Unchanged", gs)

            for status, x1, x2 in gene_rows:
                if status == "removed":
                    with st.expander(f"REMOVED  Gene id={x1.id}", expanded=False):
                        st.code("\n".join(x1.tokens), language="text")
                elif status == "added":
                    with st.expander(f"ADDED  Gene id={x2.id}", expanded=False):
                        st.code("\n".join(x2.tokens), language="text")
                else:
                    with st.expander(f"CHANGED  Gene id={x1.id}", expanded=False):
                        diff = list(difflib.unified_diff(
                            x1.tokens, x2.tokens,
                            fromfile="before", tofile="after", lineterm=""))
                        st.code("\n".join(diff), language="diff")

    class OTHER:

        def show_trna_reference():
            rows = [{"id": k, "short_name": v[0], "arity": v[1]} for k, v in sorted(BE.CST.TRNA.items())]
            st.dataframe(pandas.DataFrame(rows), use_container_width=True, hide_index=True)

