
export class IndividualParamsLinear {
    public name: string = ""
    public dimension: number = 0
    public weights: number[] = []
    public bias: number = 0

    public is_set(): boolean {
        return this.dimension === this.weights.length 
    }
}