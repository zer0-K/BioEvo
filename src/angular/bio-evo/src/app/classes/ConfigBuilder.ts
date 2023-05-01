import { config } from "rxjs"

export class ConfigBuilder {
    configs = new Map<string, Map<string, any>>()

    public constructor() { }

    public new_config(name:string) {
        if( ! (name in config) )
        {
            var instr = new Map<string, any>()
            instr.set("nb instructions", 0)

            this.configs.set(name, instr)
        }
    }

    public add_instr(cfg_name: string, instr_name:string, instr_params: any)
    {
        if( cfg_name in this.configs )
        {
            // increment number of instructions
            var nb_instr = this.configs.get(cfg_name)?.get("nb instructions")
            nb_instr += 1
            this.configs.get(cfg_name)?.set("nb instructions", nb_instr)

            // add instruction
            this.configs.get(cfg_name)?.set(
                "instruction " + nb_instr.toString(),
                { "name": instr_name, "params": instr_params }
            )
        }
    }
}