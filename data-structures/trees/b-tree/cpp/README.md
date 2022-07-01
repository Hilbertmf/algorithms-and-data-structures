properties for b tree:
- all leaves at the same level
- we can define order and degree:
clrs def:
- for minimum: a B tree has a minimum degree t:
  - minimum: all node but root minimum t children
    and t-1 keys
  - maximum: 2*t children and 2*t - 1																																																																																								 keys
knuth def:
- for a tree of order m:
  - every node can have a max. of m children and m-1 keys
  - non-leaf node w/ k children has k-1 keys
  - minimum: every node but the root has at least 
    ceil(m/2) keys and ceil(m/2) + 1 children

conditions for B tree:
- all leaves have same depth
- if a node has k keys it has k+1 children
- all internal nodes are at least half-full w/ children and keys: i.e.: t <= num children <= 2t ; t-1 <= num keys <= 2t-1

