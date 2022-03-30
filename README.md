# CLI-Binary-Tree-Visualisation
A program that visualises a binary tree in Command Line Interface

# Goal Representation

                  5                                 1 spaces (assume)


                  5
                 / \
                4   7                               3 spaces



                  5
           (e)  /   \
              4  (b)  7                             7 spaces
             / \     / \
            5   4   6   8                           3 spaces





        (a)        9        (a)                      14 - 10         6 - 4        2 - 1      (2^i - 2) - 2^(i-2)
               /       \                                             11           5          (2^(i+1) - 1) - 2^(i-1)
           5               7                         15 spaces
         /(c)\    (d)    /   \
       4       7       8       9                     7 spaces
      / \     / \     / \     / \
     5   4   6   8   4   8   4   1                   3 spaces



# Distances within various components

        (a) pow(2, height - level) - 2

        (b) pow(2, height - level + 1) - 1
                        (or)
            pow(2, height - level + 1) - digits

            where, digits is the no of digits of the previous node value to make up for extra digits

        (c)  pow(2, height - level - 1) - 1

        (d) pow(2, height - level + 1) - pow(2, height - level - 1) - 1

        (e) pow(2, height - level) - pow(2, height - level - 2) - 2



# Algorithm

        queue nodes and edges initially empty
        push head into nodes

        for i = 0 to height - 1 :
                push nodes.front into edges
                temp <- pop(nodes)
                apply (a)
                if temp != NULL print value
                else print " "
                for k = 1 to pow(2, level) - 1:
                        push nodes.front into edges
                        temp <- pop(nodes)
                        apply (b)
                        if temp != NULL print value
                        else print " "
                apply (a)
                print linefeed

                if level != height - 1:
                        apply (e)
                        for k = 0 to pow(2, level) - 1:
                                temp <- pop(edges)
                                if temp->left != NULL print "/"
                                else print " "
                                push temp->left into nodes
                                apply (c)
                                if temp->right != NULL print "\"
                                else print " "
                                push temp->right into nodes
                                apply (d)
                        apply (e)
                        print linefeed



# Key Points

        1. Values and edges are printed separately using two queue each feeding
           the other

        2. Nulls are taken into account for non-existent nodes and space
           is printed in place of edges and values
