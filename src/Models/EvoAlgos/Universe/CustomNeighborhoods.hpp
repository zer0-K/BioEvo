#pragma once

/**
 * 1 - 2D neighborhoods
 *
 * Here we suppose the universe's cells describe a 2D space
 * --> a 2*3 rectangular space is stored in 6 cells, 1st row is cells 0,1,2
 *      and second row is cells 3,4,5
 *
 * The edges of the space can be connected (mobius, torus, klein bottle, real projective plane)
 *
 */


/**
 * @brief get absolute pos of a cell in the von neumann neighborhood of another cell
 * edges are not connected
 * 
 * @param pos position of cell
 * @param pos_neighborhood position in the neighorhood of the cell
 * @param size of the neighborhood
 * @param nb_rows number of rows of the universe
 * @param nb_cols number of cols of the universe
 *
 * @return absolute position of the cell, -1 if outside of the universe
 */
inline int get_pos_from_von_neumann_neighborhood(int pos, int pos_neighborhood, int neighborhood_size, int nb_rows, int nb_cols)
{
    int nb_of_cells_von_neumann(int);

    int nb_cells_in_von_neumann_neighborhood = nb_of_cells_von_neumann(neighborhood_size);
    if(pos<0 || pos>=nb_rows*nb_cols 
        || pos_neighborhood<0 || pos_neighborhood>=nb_cells_in_von_neumann_neighborhood)
    {
        return -1;
    }

    int quarter_size = nb_cells_in_von_neumann_neighborhood/4;
    int pos_in_quarter = pos_neighborhood%quarter_size;
    int quarter = (pos_neighborhood-pos_in_quarter)/quarter_size;

    int x_in_quarter = pos_in_quarter;
    int y_in_quarter = 0; 
    for(int rsize = neighborhood_size;rsize>0 && pos_in_quarter>=rsize;rsize--)
    {
        pos_in_quarter -= rsize;
        x_in_quarter = pos_in_quarter;
        y_in_quarter++;
    }

    int x_relative;
    int y_relative;
    if(quarter==0)
    {
        x_relative = 1+x_in_quarter;
        y_relative = y_in_quarter;
    }
    else if(quarter==1)
    {
        x_relative = -y_in_quarter;
        y_relative = 1+x_in_quarter;
    }
    else if(quarter==2)
    {
        x_relative = -1-x_in_quarter;
        y_relative = -y_in_quarter;
    }
    else // last quartier
    {
        x_relative = y_in_quarter;
        y_relative = -1-x_in_quarter;
    }

    int pos_x = pos%nb_cols;
    int pos_y = (pos-pos_x)/nb_cols;

    int x_absolute = pos_x + x_relative;
    int y_absolute = pos_y + y_relative;

    if(x_absolute<0 || x_absolute>=nb_cols
        || y_absolute<0 || y_absolute>=nb_rows)
    {
        return -1;
    }

    int final_pos = x_absolute + y_absolute*nb_cols;

    return (final_pos<0 || final_pos>=nb_rows*nb_cols) ? -1 : final_pos;
}

/**
 * @brief number of cells in the von neumann neighborhood
 *
 * @param neighborhood_size size of the neighborhood
 *
 * @return nb of cells in the neighborhood
 */
inline int nb_of_cells_von_neumann(int neighborhood_size)
{
    return 2*neighborhood_size*(neighborhood_size+1);
}