# PlanetTable
This is a class program that I completed using a hash tables and the stl vector class. The point of the assignment was to use a csv file to extract planet data and then use that data to be able to search for planets that have matching values for certain attributes of the planet (e.g. Same discovery method). 

Description:

The program reads planet data from a csv file named "planets.csv" and enters it into objects.

For each line in the file, a record with the planet data and the location of the next planet with matching search values is entered into the vector.

The hash tables are used to know where the first and last item with that search value were entered, so that the planets with similar values for a search term can be found quickly.

There is a small menu that is used as an interface for the user to search for planets with certain values for their discovery method, number of planets in their solar system, temperature and name. 
