# tRNA Arity Table

Each tRNA ID consumes a fixed number of integer arguments from the DNA stream immediately following it.
Inferred from Constants.hpp comments and the naming convention (e.g. `_LV` = one local-variable index, `_cst` = one constant, `_LVLV` = two LV indices, etc.).

**Please verify and correct** — entries marked `(?)` are uncertain.

---

## Identification

tRNA IDs are in the range **[9999, 29999]**.  
In a gene, any integer outside that range following a tRNA ID is an argument to that tRNA.

---

## Variable management

| ID    | Name          | Arity | Arguments                        |
|-------|---------------|-------|----------------------------------|
| 9999  | tRNA_RET      | 0     | —                                |
| 10000 | tRNA_CVARS    | 2     | heap_pos, nb_vars                |
| 10001 | tRNA_IVARS    | 0     | — (inits from previous CVARS)    |

---

## Store / load local variables

| ID    | Name           | Arity | Arguments                 |
|-------|----------------|-------|---------------------------|
| 10100 | tRNA_SLVcst    | 2     | var_nb, cst_val           |
| 10101 | tRNA_SDLVcst   | 2     | var_nb, cst_val           |
| 10110 | tRNA_SLVLV     | 2     | dest_var_nb, src_var_nb   |
| 10111 | tRNA_SDLVLV    | 2     | dest_var_nb, src_var_nb   |
| 10112 | tRNA_SLVDLV    | 2     | dest_var_nb, src_var_nb   |
| 10113 | tRNA_SDLVDLV   | 2     | dest_var_nb, src_var_nb   |
| 10114 | tRNA_ScstLV    | 2     | addr, var_nb              |
| 10115 | tRNA_SLVaddr   | 2     | var_nb, addr              |

---

## Gene read / write

| ID    | Name         | Arity | Arguments                      |
|-------|--------------|-------|--------------------------------|
| 10150 | tRNA_RGLVLV  | 2     | dest_var_nb, gene_pos_var_nb   |
| 10170 | tRNA_WGDLV   | 3     | var_nb, var_nb, var_nb         |

---

## Get input

| ID    | Name         | Arity | Arguments                    |
|-------|--------------|-------|------------------------------|
| 10200 | tRNA_GILV    | 2     | dest_var_nb, input_index     |
| 10201 | tRNA_GDILV   | 2     | dest_var_nb, input_index     |
| 10202 | tRNA_GIDLV   | 2     | dest_var_nb, input_index     |
| 10203 | tRNA_GDIDLV  | 2     | dest_var_nb, input_index     |

---

## Stack get

| ID    | Name          | Arity | Arguments   |
|-------|---------------|-------|-------------|
| 10210 | tRNA_GTSLV    | 1     | var_nb      |
| 10211 | tRNA_GTSLVD   | 1     | var_nb      |
| 10212 | tRNA_GTSDLV   | 1     | var_nb      |
| 10250 | tRNA_GLVO     | 2     | output_index, var_nb |

---

## Control flow

| ID    | Name      | Arity | Arguments                         |
|-------|-----------|-------|-----------------------------------|
| 10500 | tRNA_IF0  | 1     | var_nb (condition variable)       |
| 10600 | tRNA_SIJ  | 0     | — (marks start of if-branch)      |
| 10700 | tRNA_SEJ  | 0     | — (marks start of else-branch)    |
| 10800 | tRNA_SWJ  | 1     | var_nb (loop condition variable)  |
| 10900 | tRNA_JLV  | 1     | var_nb                            |

---

## Stack output (push/pop)

| ID    | Name          | Arity | Arguments       |
|-------|---------------|-------|-----------------|
| 11000 | tRNA_SOScst   | 1     | cst             |
| 11001 | tRNA_SOSLV    | 1     | var_nb          |
| 11010 | tRNA_GISLV    | 1     | var_nb          |
| 11100 | tRNA_PCSI     | 1     | cst             |
| 11150 | tRNA_PLVSI    | 1     | var_nb          |
| 11200 | tRNA_PCSWI    | 1     | cst             |
| 11250 | tRNA_PLVSWI   | 1     | var_nb          |

---

## Compare

| ID    | Name            | Arity | Arguments                              |
|-------|-----------------|-------|----------------------------------------|
| 11300 | tRNA_CMPLVcst   | 4     | cmp_op, var_nb, cst, result_var_nb     |
| 11350 | tRNA_CMPLVLV    | 4     | cmp_op, var_nb1, var_nb2, result_var_nb|

---

## Arithmetic operations

| ID    | Name             | Arity | Arguments              |
|-------|------------------|-------|------------------------|
| 11400 | tRNA_OPEcstcst   | 3     | op, cst_addr, cst_val  |
| 11401 | tRNA_OPEcstLV    | 3     | op, cst_addr, var_nb   |
| 11402 | tRNA_OPELVcst    | 3     | op, var_nb, cst        |
| 11403 | tRNA_OPELVLV     | 3     | op, var_nb1, var_nb2   |

---

## Increment / decrement

| ID    | Name          | Arity | Arguments              |
|-------|---------------|-------|------------------------|
| 11450 | tRNA_INCcst   | 2     | inc_dec_flag, cst      |
| 11451 | tRNA_INCLV    | 2     | inc_dec_flag, var_nb   |
| 11452 | tRNA_INCDLV   | 2     | inc_dec_flag, var_nb   |
| 11453 | tRNA_INCS     | 1     | inc_dec_flag           |

---

## Function call

| ID    | Name           | Arity | Arguments                      |
|-------|----------------|-------|--------------------------------|
| 11500 | tRNA_CALLcst   | 1     | func_id                        |
| 11501 | tRNA_CALLLV    | 1     | var_nb (holds func_id)         |

---

## Recursive unsigned integer (RUI)

| ID    | Name             | Arity | Arguments                 |
|-------|------------------|-------|---------------------------|
| 11600 | tRNA_RUIcstcst   | 3     | result_var, cst1, cst2    |
| 11601 | tRNA_RUIcstLV    | 3     | result_var, cst, var_nb   |
| 11602 | tRNA_RUILVcst    | 3     | result_var, var_nb, cst   |
| 11603 | tRNA_RUILVLV     | 3     | result_var, var_nb1, var_nb2 |

---

## Gene op

| ID    | Name           | Arity | Arguments         |
|-------|----------------|-------|-------------------|
| 12000 | tRNA_GScstcst  | 2     | cst, cst          |
| 12001 | tRNA_GScstLV   | 2     | cst, var_nb       |
| 12002 | tRNA_GSLVcst   | 2     | var_nb, cst       |
| 12003 | tRNA_GSLVLV    | 2     | var_nb1, var_nb2  |
| 12500 | tRNA_GADD      | 2     | var_nb, cst       |

---

## Universe interaction

| ID    | Name        | Arity | Arguments         |
|-------|-------------|-------|-------------------|
| 13000 | tRNA_USLV   | 1     | var_nb            |
| 13001 | tRNA_RULV   | 1     | var_nb            |
| 13100 | tRNA_EMPTY  | 2     | var_nb, var_nb    |
| 13200 | tRNA_WRITE  | 2     | var_nb, var_nb    |

---

## Halt

| ID    | Name       | Arity | Arguments |
|-------|------------|-------|-----------|
| 14999 | tRNA_HALT  | 0     | —         |

---

## Meta tRNAs (used internally in tRNA definitions)

These appear in genes that define other tRNAs (meta-processors). Arities are uncertain — they may not appear in regular user-written genes.

| ID    | Name          | Arity  | Notes                            |
|-------|---------------|--------|----------------------------------|
| 14000 | tRNA_MP       | 0      | P-site init                      |
| 14010 | tRNA_ME       | 0      | E-site init                      |
| 14100 | tRNA_Mcst     | 1      | cst value                        |
| 14101 | tRNA_M0       | 0      | arg slot 0 marker                |
| 14102 | tRNA_M1       | 0      | arg slot 1 marker                |
| 14103 | tRNA_M2       | 0      | arg slot 2 marker                |
| 14104 | tRNA_M3       | 0      | arg slot 3 marker                |
| 14200 | tRNA_MInstr   | 1      | meta instruction                 |
| 14201 | tRNA_MCPY     | 0      | copies P-site template           |
| 14300 | tRNA_Marg     | 0      | meta argument                    |
| 14301 | tRNA_MargW    | 0      | meta argument write              |
| 14310 | tRNA_MLV      | 0      | meta local var                   |
| 14311 | tRNA_MLVW     | 0      | meta local var                   |

---

## Special / stack pointer tRNAs

| ID    | Name              | Arity  | Arguments                  |
|-------|-------------------|--------|----------------------------|
| 15000 | tRNA_SP_GPTR      | 0      | —                          |
| 15001 | tRNA_SP_FCTADD    | 0      | function address           |
| 15002 | tRNA_SP_GFPTRLV   | 1      | var_nb                     |
| 15003 | tRNA_SP_GSPLV     | 1      | var_nb                     |
| 15004 | tRNA_SP_GCPY      | 3      | var_nb, var_nb, var_nb     |
