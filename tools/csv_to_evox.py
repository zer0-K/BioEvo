#!/usr/bin/env python3
"""Convert body_*.csv to .evox format."""

import sys

OPCODES = {
    0: 'XXX', 1: 'MOV', 2: 'CPY', 3: 'CPYIN', 4: 'CPYOUT', 5: 'INC', 6: 'DEC',
    7: 'ADD', 8: 'SUB', 9: 'MUL', 10: 'DIV', 11: 'OPP', 12: 'CPYIS', 13: 'SETOS',
    14: 'CPYUS', 15: 'EMPTY', 16: 'READ', 17: 'WRITE', 18: 'CMP',
    19: 'JMP', 20: 'JRA', 21: 'JRS', 22: 'JE', 23: 'JL', 24: 'JG',
    25: 'JLE', 26: 'JGE', 27: 'JRE', 28: 'JRL', 29: 'JRG', 30: 'JRLE', 31: 'JRGE',
    32: 'GPTR', 33: 'BEG', 34: 'HALT', 35: 'RUD', 36: 'RUI', 37: 'RN', 38: 'RG',
    39: 'GR', 40: 'GINS', 41: 'GDEL', 42: 'GDELW', 43: 'GSET', 44: 'GADD',
    45: 'GCPY', 46: 'MARKER', 47: 'GCPYM', 48: 'EXEC', 49: 'CALL', 50: 'REGEN',
}

TRNA_NAMES = {
    9999: 'RET', 10000: 'CVARS', 10001: 'IVARS',
    10100: 'SLVcst', 10101: 'SDLVcst', 10110: 'SLVLV', 10111: 'SDLVLV',
    10112: 'SLVDLV', 10113: 'SDLVDLV', 10114: 'ScstLV', 10115: 'SLVaddr',
    10150: 'RGLVLV', 10170: 'WGDLV',
    10200: 'GILV', 10201: 'GDILV', 10202: 'GIDLV', 10203: 'GDIDLV',
    10210: 'GTSLV', 10211: 'GTSLVD', 10212: 'GTSDLV', 10250: 'GLVO',
    10500: 'IF0', 10600: 'SIJ', 10700: 'SEJ', 10800: 'SWJ', 10900: 'JLV',
    11000: 'SOScst', 11001: 'SOSLV', 11010: 'GISLV',
    11100: 'PCSI', 11150: 'PLVSI', 11200: 'PCSWI', 11250: 'PLVSWI',
    11300: 'CMPLVcst', 11350: 'CMPLVLV',
    11400: 'OPEcstcst', 11401: 'OPEcstLV', 11402: 'OPELVcst', 11403: 'OPELVLV',
    11450: 'INCcst', 11451: 'INCLV', 11452: 'INCDLV', 11453: 'INCS',
    11500: 'CALLcst', 11501: 'CALLLV',
    11600: 'RUIcstcst', 11601: 'RUIcstLV', 11602: 'RUILVcst', 11603: 'RUILVLV',
    12000: 'GScstcst', 12001: 'GScstLV', 12002: 'GSLVcst', 12003: 'GSLVLV',
    12500: 'GADD', 13000: 'USLV', 13001: 'RULV',
    13100: 'EMPTY', 13200: 'WRITE', 14999: 'HALT',
    14000: 'MP', 14010: 'ME',
    14100: 'Mcst', 14101: 'M0', 14102: 'M1', 14103: 'M2', 14104: 'M3',
    14200: 'MInstr', 14201: 'MCPY',
    14300: 'Marg', 14301: 'MargW', 14310: 'MLV', 14311: 'MLVW',
    15000: 'SP_GPTR', 15001: 'SP_FCTADD', 15002: 'SP_GFPTRLV',
    15003: 'SP_GSPLV', 15004: 'SP_GCPY',
}

TRNA_ARITIES = {
    9999: 0, 10000: 2, 10001: 0,
    10100: 2, 10101: 2, 10110: 2, 10111: 2, 10112: 2, 10113: 2, 10114: 2, 10115: 2,
    10150: 2, 10170: 3,
    10200: 2, 10201: 2, 10202: 2, 10203: 2, 10210: 1, 10211: 1, 10212: 1, 10250: 2,
    10500: 1, 10600: 0, 10700: 0, 10800: 1, 10900: 1,
    11000: 1, 11001: 1, 11010: 1, 11100: 1, 11150: 1, 11200: 1, 11250: 1,
    11300: 4, 11350: 4,
    11400: 3, 11401: 3, 11402: 3, 11403: 3,
    11450: 2, 11451: 2, 11452: 2, 11453: 1,
    11500: 1, 11501: 1,
    11600: 3, 11601: 3, 11602: 3, 11603: 3,
    12000: 2, 12001: 2, 12002: 2, 12003: 2,
    12500: 2, 13000: 1, 13001: 1,
    13100: 2, 13200: 2, 14999: 0,
    14000: 0, 14010: 0,
    14100: 1, 14101: 0, 14102: 0, 14103: 0, 14104: 0,
    14200: 1, 14201: 0,
    14300: 0, 14301: 0, 14310: 0, 14311: 0,
    15000: 0, 15001: 0, 15002: 1, 15003: 1, 15004: 3,
}

GSTART_ID = -51451
GSTOP_ID  = -77142


def parse_csv(path):
    rows = []
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            parts = [int(x.strip()) for x in line.rstrip(',').split(',')]
            if len(parts) == 7:
                rows.append(parts)
    return rows


def fmt_row(row, indent='    '):
    """Format a 7-int row as XASM instruction (opcode name + 6 int args)."""
    opcode = row[0]
    name = OPCODES.get(opcode, str(opcode))
    return indent + name + ' ' + ' '.join(str(x) for x in row[1:])


def fmt_raw_row(row, indent='    '):
    """Format a 7-int row as raw integers (for RAW/TRAIL sections)."""
    return indent + ' '.join(str(x) for x in row)


def fmt_dna_content(content, indent='        '):
    lines = []
    i = 0
    while i < len(content):
        val = content[i]
        name = TRNA_NAMES.get(val)
        if name is not None:
            arity = TRNA_ARITIES.get(val, 0)
            args = content[i + 1 : i + 1 + arity]
            line = indent + name
            if args:
                line += ' ' + ' '.join(str(a) for a in args)
            lines.append(line)
            i += 1 + arity
        else:
            lines.append(indent + str(val))
            i += 1
    return lines


def convert(csv_path, evox_path):
    rows = parse_csv(csv_path)

    # Find DNA section (pair of MARKER(-1): row[0]==46, row[1]==0, row[2]==-1)
    dna_start = dna_end = None
    for i, r in enumerate(rows):
        if r[0] == 46 and r[1] == 0 and r[2] == -1:
            if dna_start is None:
                dna_start = i
            else:
                dna_end = i
                break

    # Rows after DNA end marker → TRAIL section
    trail_rows = rows[dna_end + 1:] if dna_end is not None else []

    # XASM section: everything before DNA start marker
    xasm_rows = rows[:dna_start]

    # RAW header: first 2 rows (config + JMP, before first PROGTEIN marker)
    raw_header = xasm_rows[:2]

    # Progtein section: pairs of MARKER(id) wrapping instructions
    progtein_rows = xasm_rows[2:]
    progteins = []   # list of (id, [instruction rows])
    i = 0
    while i < len(progtein_rows):
        r = progtein_rows[i]
        if r[0] == 46 and r[1] == 0 and r[2] >= 0:
            pid = r[2]
            body_instrs = []
            i += 1
            while i < len(progtein_rows):
                cur = progtein_rows[i]
                if cur[0] == 46 and cur[1] == 0 and cur[2] == pid:
                    body_instrs.append(cur)  # include end-marker in body
                    i += 1
                    break
                body_instrs.append(cur)
                i += 1
            progteins.append((pid, body_instrs))
        else:
            i += 1

    # DNA: flatten rows between markers, parse genes
    dna_flat = [v for row in rows[dna_start + 1 : dna_end] for v in row]
    genes = []
    j = 0
    while j < len(dna_flat):
        if dna_flat[j] == GSTART_ID:
            gene_id = dna_flat[j + 1]
            j += 2
            content = []
            while j < len(dna_flat) and dna_flat[j] != GSTOP_ID:
                content.append(dna_flat[j])
                j += 1
            if j < len(dna_flat):
                j += 1  # skip GSTOP_ID
            genes.append((gene_id, content))
        else:
            j += 1

    # Per-gene padding is now handled by the assembler (each gene padded to 7-int boundary).
    # Compute any remaining global padding beyond what per-gene alignment produces.
    per_gene_total = sum(((3 + len(c) + 6) // 7) * 7 for _, c in genes)  # round up each
    dna_extra_pad = len(dna_flat) - per_gene_total  # should be 0 for well-formed bodies

    # Write .evox
    with open(evox_path, 'w') as f:
        f.write('RAW\n')
        for row in raw_header:
            f.write(fmt_raw_row(row) + '\n')
        f.write('END\n\n')

        for pid, instrs in progteins:
            name = TRNA_NAMES.get(pid)
            label = f' {name}' if name else ''
            f.write(f'PROGTEIN{label} id={pid}\n')
            for row in instrs:
                f.write(fmt_row(row) + '\n')
            f.write('END\n\n')

        f.write('DNA\n')
        for gid, content in genes:
            f.write(f'    GENE id={gid}\n')
            for line in fmt_dna_content(content):
                f.write(line + '\n')
            f.write('    END\n')
        if dna_extra_pad > 0:
            f.write(f'    PAD {dna_extra_pad}\n')
        f.write('END\n')

        if trail_rows:
            f.write('\nTRAIL\n')
            for row in trail_rows:
                f.write(fmt_raw_row(row) + '\n')
            f.write('END\n')

    print(f'Converted: {len(rows)} rows, {len(progteins)} progteins, '
          f'{len(genes)} genes, {len(trail_rows)} trail rows → {evox_path}')


if __name__ == '__main__':
    csv  = sys.argv[1] if len(sys.argv) > 1 else 'data/body_transcribed.csv'
    evox = sys.argv[2] if len(sys.argv) > 2 else csv.replace('.csv', '.evox')
    convert(csv, evox)
