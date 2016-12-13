-   [Skip List](#skip-list)
    -   [Logarithmic](#logarithmic)
    -   [Linear](#linear)
-   [Binary Search Tree](#binary-search-tree)
    -   [Logarithmic](#logarithmic-1)
    -   [Linear](#linear-1)
-   [Linked List](#linked-list)
    -   [Logarithmic](#logarithmic-2)
    -   [Linear](#linear-2)
-   [Skip List + Binary Search Tree](#skip-list-binary-search-tree)

This is an [R Markdown](http://rmarkdown.rstudio.com) Notebook.

Load libraries and read in data:

``` r
library(ggplot2)
library(scales)
```

Skip List
=========

Logarithmic
-----------

![](SkipListAnalysis_files/figure-markdown_github/Skip%20List%20Logarithmic%20Regression-1.png)

R<sup>2</sup> values for each operation:

    ## delete: 0.709693
    ## insert: 0.700800
    ## search: 0.690260

Linear
------

![](SkipListAnalysis_files/figure-markdown_github/Skip%20List%20Linear%20Regression-1.png)

R<sup>2</sup> values for each operation:

    ## delete: 0.869304
    ## insert: 0.865875
    ## search: 0.895552

Binary Search Tree
==================

Logarithmic
-----------

![](SkipListAnalysis_files/figure-markdown_github/Binary%20Search%20Tree%20Logarithmic%20Regression-1.png)

R<sup>2</sup> values for each operation:

    ## delete: 0.751767
    ## insert: 0.910839
    ## search: 0.899026

Linear
------

![](SkipListAnalysis_files/figure-markdown_github/Binary%20Search%20Tree%20Linear%20Regression-1.png)

R<sup>2</sup> values for each operation:

    ## delete: 0.806583
    ## insert: 0.658275
    ## search: 0.673133

Linked List
===========

Logarithmic
-----------

![](SkipListAnalysis_files/figure-markdown_github/Linked%20List%20Logarithmic%20Regression-1.png)

R<sup>2</sup> values for each operation:

    ## delete: 0.502836
    ## insert: 0.497537
    ## search: 0.511234

Linear
------

![](SkipListAnalysis_files/figure-markdown_github/Linked%20List%20Linear%20Regression-1.png)

R<sup>2</sup> values for each operation:

    ## delete: 0.996232
    ## insert: 0.995147
    ## search: 0.997242

Skip List + Binary Search Tree
==============================

![](SkipListAnalysis_files/figure-markdown_github/Double%20Logarithmic%20Regression-1.png)
