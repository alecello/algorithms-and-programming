#include <stdio.h>
#include <stdlib.h>

#define STANDARD 0
#define INVERTED 1

struct parcel
{
   int x;
   int y;

   int xPos;
   int yPos;

   int orientation;
};

int solve(int count, struct parcel *parcels);
int recurse(int index, int count, struct parcel *parcels, int **grid, int xDimension, int yDimension);
int place(struct parcel item, int id, int **grid, int x, int y, int xDimension, int yDimension);

void clear(struct parcel item, int **grid, int gridXDimension, int gridYDimension);

int main(int argc, char **argv)
{
   int parcelNumber;
   FILE *file;

   if(argc != 2)
      file = fopen("input.txt", "r");
   else
      file = fopen(argv[1], "r");

   if(file == NULL)
   {
      fprintf(stderr, "ERROR: Failed to open file %s in read-only mode!\n", argv[1]);
      exit(EXIT_FAILURE);
   }

   fscanf(file, " %d", &parcelNumber);
   struct parcel *parcels = malloc(parcelNumber * sizeof(struct parcel));

   for(int i = 0; i < parcelNumber; ++i)
      fscanf(file, " %dx%d", &parcels[i].x, &parcels[i].y);

   solve(parcelNumber, parcels);
}

int solve(int count, struct parcel *parcels)
{
   int returnValue;
   int sizes = 4;

   int xDimensions[] = {10, 10, 15, 20};
   int yDimensions[] = {15, 20, 25, 30};

   for(int i = 0; i < sizes; ++i)
   {
      int **grid = (int **) malloc(xDimensions[i] * sizeof(int *));

      for(int j = 0; j < xDimensions[i]; ++j)
         grid[j] = (int *) calloc(yDimensions[i], sizeof(int));

      returnValue = recurse(0, count, parcels, grid, xDimensions[i], yDimensions[i]);
      free(grid);

      if(returnValue == EXIT_SUCCESS)
         return EXIT_SUCCESS;
   }

   return EXIT_FAILURE;
}

int recurse(int index, int count, struct parcel *parcels, int **grid, int xDimension, int yDimension)
{
   int returnValue;

   if(index == count)
   {
      printf("A %dx%d truck is sufficient to carry this payload.\n\n", xDimension, yDimension);

      putchar('*');
      for(int i = 0; i < yDimension; ++i)
         putchar('-');
      printf("*\n");

      for(int x = 0; x < xDimension; ++x)
      {
         putchar('|');

         for(int y = 0; y < yDimension; ++y)
            printf("%c", (grid[x][y] != 0) ? '0' + grid[x][y] : ' ');

         printf("|\n");
      }

      putchar('*');
      for(int i = 0; i < yDimension; ++i)
         putchar('-');
      printf("*\n");

      return EXIT_SUCCESS;
   }

   for(int x = 0; x < xDimension; ++x)
      for(int y = 0; y < yDimension; ++y)
      {
         if(place(parcels[index], (index + 1), grid, x, y, xDimension, yDimension) == EXIT_SUCCESS)
         {
            returnValue = recurse((index + 1), count, parcels, grid, xDimension, yDimension);

            if(returnValue == EXIT_SUCCESS)
               return EXIT_SUCCESS;

            clear(parcels[index], grid, xDimension, yDimension);
         }
      }

   return EXIT_FAILURE;
}

int place(struct parcel item, int id, int **grid, int x, int y, int xDimension, int yDimension)
{
   int validSolution = 1;

   if(x + item.x <= xDimension && y + item.y <= yDimension)
   {
      for(int xx = x; xx < x + item.x && validSolution; ++xx)
         for(int yy = y; yy < y + item.y && validSolution; ++yy)
            if(grid[xx][yy] != 0)
               validSolution = 0;

      if(validSolution)
      {
         item.orientation = STANDARD;
         item.xPos = x;
         item.yPos = y;

         for(int xx = x; xx < x + item.x; ++xx)
            for(int yy = y; yy < y + item.y; ++yy)
               grid[xx][yy] = id;

         return EXIT_SUCCESS;
      }
   }

   // attempt in other orientation
   if(x + item.y <= xDimension && y + item.x <= yDimension)
   {
      validSolution = 1;

      for(int xx = x; xx < x + item.y && validSolution; ++xx)
         for(int yy = y; yy < y + item.x && validSolution; ++yy)
            if(grid[xx][yy] != 0)
               validSolution = 0;

      if(validSolution)
      {
         item.orientation = INVERTED;
         item.xPos = x;
         item.yPos = y;

         for(int xx = x; xx < x + item.y; ++xx)
            for(int yy = y; yy < y + item.x; ++yy)
               grid[xx][yy] = id;

         return EXIT_SUCCESS;
      }
   }

   return EXIT_FAILURE;
}

void clear(struct parcel item, int **grid, int gridXDimension, int gridYDimension)
{
   int xDimension = (item.orientation == STANDARD) ? item.x : item.y;
   int yDimension = (item.orientation == INVERTED) ? item.y : item.x;

   int xBound = item.xPos + xDimension;
   int yBound = item.yPos + yDimension;

   int xLimit = (xBound < gridXDimension) ? xBound : gridXDimension;
   int yLimit = (yBound < gridYDimension) ? yBound : gridYDimension;

   for(int x = item.xPos; x < xLimit; ++x)
      for(int y = item.yPos; y < yLimit; ++y)
         grid[x][y] = 0;

}
