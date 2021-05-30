# SORTED-STACKLESS-BST
This program implements template class of node and SortedStacklessBST. Implement functions in SortedStacklessBST

## Problem
<p>Binary Search Trees are mainly used to store ordered data but to access the data in sorted order one would need 
stack. In order to access the data in sorted order without stack we use an additional data member nextInOrder in 
the node (a pointer to node for the successor or predecessor). We may want to access the data in ascending order 
or in descending order. So the nextInOrder will either point to the successor node or predecessor node. A 
Boolean variable IsSuccessor will be added in the class BST. If IsSuccessor is true then all the nextInOrder
pointers will be pointing towards their successor nodes and maximum data node’s pointer will be nullptr. 
Otherwise these pointers will point to their predecessor nodes and minimum data node’s pointer will be nullptr.</p>

## To Compile:
<pre><code>g++ Source.cpp -o main </code></pre>

## To execute:
<pre><code>./main</code></pre>
