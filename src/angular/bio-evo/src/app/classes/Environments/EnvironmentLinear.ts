

export class EnvironmentParamsLinear {
    public name: string = ""
    public dimension: number
    public w: number[]
    public b: number


    public current_weight_index = 0

    constructor() {
        this.name = ""
        this.dimension = 0
        this.w = []
        this.b = 0
    }

    public setname(name: string): void {
        this.name = name
    }

    public set_weights_at_end(val: number, nb_times:number): void {

        for(let i=this.current_weight_index;i<Math.min(this.dimension, this.current_weight_index+ nb_times); i++) {
            this.w.push(val)
        }
        this.current_weight_index += nb_times
    } 
}
