#include "treePublic.h"
#include "treeAddition.h"

#define OK 1
#define KO 0

int
main (
  void
   )
{
  node_t *root, *tmp;
  data_t d;
  int retValue, end = 0;
  char row[MAXC];
  FILE *fp = NULL;

  int h, number, sum, k1, k2, distance, children[3], *levels;

  root = NULL;
  root = createEmptyTree();

  while (!end) {

    fprintf (stdout, "User selection\n");
    fprintf (stdout, "\t01) Insert one single node\n\t02) Cancel one single node\n\t03) Search a node\n");
    fprintf (stdout, "\t04) Print BST on stdout\n\t05) Write BST on file\n\t06) Read BST from file\n");
    fprintf (stdout, "\t07) Compute min and max\n\t08) Print children number statistics for tree\n");
    fprintf (stdout, "\t09) Compute nodes in each level of the tree\n");
    fprintf (stdout, "\t10) Compute number of paths to leaf and sum of their lengths\n");
    fprintf (stdout, "\t11) Compute distance between two keys\n\t12) End\n\t> ");
    scanf ("%s", row);

    switch (atoi(row)) {
      case 1:
        fprintf (stdout, "data: ");
	      retValue = readData (stdin, &d);
        if (retValue==0) {
          fprintf (stderr, "Input erro.\n");
          exit (0);
        }
	      root = insert (root, d);
	      break;

      case 2:
        fprintf (stdout, "data: ");
	      retValue = readData (stdin, &d);
        if (retValue==0) {
          fprintf (stderr, "Input erro.\n");
          exit (0);
        }
	      root = delete (root, d);
	      break;

      case 3:
        fprintf (stdout, "data: ");
	      retValue = readData (stdin, &d);
        if (retValue==0) {
          fprintf (stderr, "Input error.\n");
          exit (0);
        }

	      tmp = searchI (root, d);
	      if (tmp != NULL) {
	        fprintf (stdout, "Iterative Search: Found -> ");
                writeData (stdout, getData(tmp));
	      } else {
	        fprintf (stdout, "Iterative Search: Not Found\n");
        }
	      tmp = searchR (root, d);
	      if (tmp  != NULL) {
	        fprintf (stdout, "Recursive Search: Found -> ");
                writeData (stdout, getData(tmp));
	      } else {
	        fprintf (stdout, "Recursive Search: Not Found\n");
        }
	      break;

      case 4:
	      writeTree (stdout, root, INORDER);
	      break;

      case 5:
	      fprintf (stdout, "File Name: ");
	      scanf ("%s", row);

        if (strcmp (row, "stdout") == 0) {
          fp = stdout;
        } else {
   	      fp = fopen (row, "w");
        }

        if (fp == NULL) {
          fprintf (stderr, "Error Opening File %s\n", row);
          break;
	      }

	      writeTree (fp, root, PREORDER);

        if (strcmp (row, "stdout") != 0) {
	        fclose(fp);
	      }
	      break;

      case 6:
	      fprintf (stdout, "File Name: ");
	      scanf ("%s", row);

	      fp = fopen (row, "r");
	      if (fp == NULL) {
	        fprintf (stderr, "Error Opening File %s\n", row);
	      } else {
	        freeTree (root);
	        root = readTree (fp);
	      }
	      break;

      case 7:
        fprintf (stdout, "Tree minimum iterative: "); 
        tmp = treeMinI (root);
        writeData (stdout, getData(tmp));
        fprintf (stdout, "Tree minimum recursive: "); 
        tmp = treeMinR (root);
        writeData (stdout, getData(tmp));
        fprintf (stdout, "Tree maximum iterative: ");
        tmp = treeMaxI (root);
        writeData (stdout, getData(tmp));
        fprintf (stdout, "Tree maximum recursive: "); 
        tmp = treeMaxR (root);
        writeData (stdout, getData(tmp));
	      break;

      case 8:
        countNode(root, children);
        fprintf(stdout, "Nodes with 0 children: %d\n", children[0]);
        fprintf(stdout, "Nodes with 1 children: %d\n", children[1]);
        fprintf(stdout, "Nodes with 2 children: %d\n", children[2]);
        break;
      
      case 9:
        fprintf(stdout, "Tree height: ");
        fscanf(stdin, "%d", &h);

        levels = calloc(h, sizeof(int));
        countLevel(root, levels, h);

        for(int i = 0; i < h; ++i)
          printf("Level %d: %d\n", i, levels[i]);
        
        free(levels);
        break;
      
      case 10:
        countPath(root, &number, &sum);
        fprintf(stdout, "There is a total of %d paths to leaves, with a total sum of %d edges\n", number, sum);
        break;

      case 11:
        fprintf(stdout, "Key 1: ");
        fscanf(stdin, "%d", &k1);
        fprintf(stdout, "Key 2: ");
        fscanf(stdin, "%d", &k2);

        distance = visit(root, k1, k2);

        if(distance >= 0)
          fprintf(stdout, "There are %d edges of distance between %d and %d\n", distance, k1, k2);
        else
          fprintf(stdout, "Error 404 - Not found.\n");
        break;

      case 12:
	      end = 1;
	      break;

      default:
	      fprintf (stderr, "Unknown Option.\n");
	      break;
    }
  }

  freeTree(root);

  return (OK);
}



