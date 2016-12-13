-   [Skip List](#skip-list)
-   [Binary Search Tree](#binary-search-tree)
-   [Linked List](#linked-list)

This is an [R Markdown](http://rmarkdown.rstudio.com) Notebook.

Load libraries and read in data:

``` r
library(ggplot2)
library(scales)

df <- read.csv("timing_results.csv")
df.sl <- subset(df, structure == "skip list")
df.bst <- subset(df, structure == "binary tree")
df.ll <- subset(df, structure == "linked list")
df.sl.short <- subset(df.sl, n <= 100000)
df.double <- subset(df, structure %in% c("binary tree", "skip list"))


scientific_10 = function(x) {parse(text=gsub("e", "%*%10^", scientific_format()(x)))}
log10_minor_break = function (...){
  function(x) {
    minx         = floor(min(log10(x), na.rm=T))-1;
    maxx         = ceiling(max(log10(x), na.rm=T))+1;
    n_major      = maxx-minx+1;
    major_breaks = seq(minx, maxx, by=1)
    minor_breaks = 
      rep(log10(seq(1, 9, by=1)), times = n_major)+
      rep(major_breaks, each = 9)
    return(10^(minor_breaks))
  }
}
Rsq_log = function(x) {
  for (op in c("delete", "insert", "search")) {
    df.r2 <- subset(x, operation == op)
    fit <- lm(log10(df.r2$n) ~ df.r2$tpo)
    cat(sprintf("%s: %f\n", op, summary(fit)$adj.r.squared))
  }
}

Rsq_lin = function(x) {
    for (op in c("delete", "insert", "search")) {
    df.r2 <- subset(x, operation == op)
    fit <- lm(df.r2$n ~ df.r2$tpo)
    cat(sprintf("%s: %f\n", op, summary(fit)$adj.r.squared))
    }
}
```

Skip List
=========

``` r
p_log.sl <- ggplot(data=df.sl, aes(n, tpo, color = operation)) +
  geom_point(size = 0.5) +
  geom_smooth(formula = tpo ~ n, method = "lm", size = 0.5, color = "gray50") +
  labs(title="Skip List Operations with Logarithmic Regression", x="n", y="Time per Operation (\u03BCs)") +
  theme(plot.title = element_text(hjust=0.5),
        legend.position = "none",
        panel.spacing = unit(1, "lines"),
        panel.border = element_rect(fill=NA, color="gray90", size=0.5, linetype="solid"),
        panel.background = element_rect(fill = "gray90"),
        panel.grid.minor.x = element_line(size=0.1)) +
  # scale_x_log10(limits = c(1,1e8)) + ylim(0,4) + 
    coord_trans(x="log10") +
    ylim(0,5) +
  scale_x_continuous(breaks = scales::trans_breaks("log10", function(x) 10^x), minor_breaks = log10_minor_break(), labels = scales::trans_format("log10", scales::math_format(10^.x))) +
  # minor_breaks=log10_minor_break()
  # scales::trans_breaks("log10", function(x) 10^x)
  facet_grid(. ~ operation)
p_log.sl
```

![](SkipListAnalysis_files/figure-markdown_github/Skip%20List%20Logarithmic%20Regression-1.png) R<sup>2</sup> values for each operation:

``` r
Rsq_log(df.sl)
```

    ## delete: 0.709693
    ## insert: 0.700800
    ## search: 0.690260

``` r
p_log.sl.short <- ggplot(data=df.sl.short, aes(log10(n), tpo, color = operation)) +
  geom_point(size = 0.5) +
  #geom_smooth(method="lm", size = 0.5, color = "gray50") +
  labs(title="Skip List Operations with Logarithmic Regression Short Data", x=expression(Log[10](n)), y="Time per Operation (\u03BCs)") +
  theme(plot.title = element_text(hjust=0.5),
        legend.position = "none",
        panel.spacing = unit(1, "lines"),
        panel.border = element_rect(fill=NA, color="gray90", size=0.5, linetype="solid"),
        panel.background = element_rect(fill = "gray90")) +
  # xlim(0,5) + ylim(0,4) + 
  facet_grid(. ~ operation)
p_log.sl.short
```

![](SkipListAnalysis_files/figure-markdown_github/Skip%20List%20Logarithmic%20Regression%20Short%20Data-1.png)

``` r
#Rsq_log(df.sl.short)
df.r2 <- subset(df.sl.short, operation == "insert")
fit <- lm(log10(df.r2$n) ~ log10(df.r2$tpo))
summary(fit)$adj.r.squared
```

    ## [1] 0.6831212

``` r
p_linear.sl <- ggplot(data=df.sl, aes(n / 10^6, tpo, color = operation)) +
  geom_point(size = 0.5) +
  #geom_smooth(method="lm", size = 0.5, color = "gray50") +
  labs(title="Skip List Operations with Linear Regression", x=expression("n "*(10^6)), y="Time per Operation (\u03BCs)") +
  theme(plot.title = element_text(hjust=0.5),
        legend.position = "none",
        panel.spacing = unit(1, "lines"),
        panel.border = element_rect(fill=NA, color="gray90", size=0.5, linetype="solid"),
        panel.background = element_rect(fill = "gray90")) +
  scale_x_continuous(breaks = c(0, 2, 4, 6, 8, 10)) +
  facet_grid(. ~ operation)
p_linear.sl
```

![](SkipListAnalysis_files/figure-markdown_github/Skip%20List%20Linear%20Regression-1.png)

``` r
Rsq_lin(df.sl)
```

    ## delete: 0.869304
    ## insert: 0.865875
    ## search: 0.895552

Binary Search Tree
==================

``` r
p_log.bst <- ggplot(data=df.bst, aes(n, tpo, color = operation)) +
  geom_point(size = 0.5) +
  #geom_smooth(method="lm", size = 0.5, color = "gray50") +
  labs(title="Binary Search Tree Operations with Logarithmic Regression", x="n", y="Time per Operation (\u03BCs)") +
  theme(plot.title = element_text(hjust=0.5),
        legend.position = "none",
        panel.spacing = unit(1, "lines"),
        panel.border = element_rect(fill=NA, color="gray90", size=0.5, linetype="solid"),
        panel.background = element_rect(fill = "gray90"),
        panel.grid.minor.x = element_line(size=0.1)) +
  coord_trans(x="log10") +
  ylim(0,2) +
  scale_x_continuous(breaks = scales::trans_breaks("log10", function(x) 10^x),  minor_breaks = log10_minor_break(), labels = scales::trans_format("log10", scales::math_format(10^.x))) +
  facet_grid(. ~ operation)
p_log.bst
```

![](SkipListAnalysis_files/figure-markdown_github/Binary%20Search%20Tree%20Logarithmic%20Regression-1.png)

``` r
Rsq_log(df.bst)
```

    ## delete: 0.751767
    ## insert: 0.910839
    ## search: 0.899026

``` r
p_linear.bst <- ggplot(data=df.bst, aes(n / 10^6, tpo, color = operation)) +
  geom_point(size = 0.5) +
  #geom_smooth(method="lm", size = 0.5, color = "gray50") +
  labs(title="Binary Search Tree Operations with Linear Regression", x=expression("n "*(10^6)), y="Time per Operation (\u03BCs)") +
  theme(plot.title = element_text(hjust=0.5),
        legend.position = "none",
        panel.spacing = unit(1, "lines"),
        panel.border = element_rect(fill=NA, color="gray90", size=0.5, linetype="solid"),
        panel.background = element_rect(fill = "gray90")) +
  ylim(0,2.1) +
  scale_x_continuous(breaks = c(0, 2, 4, 6, 8, 10)) +
  facet_grid(. ~ operation)
p_linear.bst
```

![](SkipListAnalysis_files/figure-markdown_github/Binary%20Search%20Tree%20Linear%20Regression-1.png)

``` r
Rsq_lin(df.bst)
```

    ## delete: 0.806583
    ## insert: 0.658275
    ## search: 0.673133

Linked List
===========

``` r
p_log.ll <- ggplot(data=df.ll, aes(n, tpo, color = operation)) +
  geom_point(size = 0.5) +
  #geom_smooth(method="lm", size = 0.5, color = "gray50") +
  labs(title="Linked List Operations with Logarithmic Regression", x="n", y="Time per Operation (\u03BCs)") +
  theme(plot.title = element_text(hjust=0.5),
        legend.position = "none",
        panel.spacing = unit(1, "lines"),
        panel.border = element_rect(fill=NA, color="gray90", size=0.5, linetype="solid"),
        panel.background = element_rect(fill = "gray90"),
        panel.grid.minor.x = element_line(size=0.1)) +
  coord_trans(x="log10") +
  scale_x_continuous(breaks = scales::trans_breaks("log10", function(x) 10^x),  minor_breaks = log10_minor_break(), labels = scales::trans_format("log10", scales::math_format(10^.x))) +
  ylim(0, 450) +
  facet_grid(. ~ operation)
p_log.ll
```

![](SkipListAnalysis_files/figure-markdown_github/Linked%20List%20Logarithmic%20Regression-1.png)

``` r
Rsq_log(df.ll)
```

    ## delete: 0.502836
    ## insert: 0.497537
    ## search: 0.511234

``` r
p_linear.ll <- ggplot(data=df.ll, aes(n / 10^4, tpo, color = operation)) +
  geom_point(size = 0.5) +
  #geom_smooth(method="lm", size = 0.5, color = "gray50") +
  labs(title="Linked List Operations with Linear Regression", x=expression("n "*(10^4)), y="Time per Operation (\u03BCs)") +
  theme(plot.title = element_text(hjust=0.5),
        legend.position = "none",
        panel.spacing = unit(1, "lines"),
        panel.border = element_rect(fill=NA, color="gray90", size=0.5, linetype="solid"),
        panel.background = element_rect(fill = "gray90")) +
  scale_x_continuous(breaks = c(0, 2, 4, 6, 8, 10)) +
  facet_grid(. ~ operation)
p_linear.ll
```

![](SkipListAnalysis_files/figure-markdown_github/Linked%20List%20Linear%20Regression-1.png)

``` r
Rsq_lin(df.ll)
```

    ## delete: 0.996232
    ## insert: 0.995147
    ## search: 0.997242

``` r
p_log.double <- ggplot(data=df.double, aes(n, tpo, color = structure)) +
  geom_point(size = 0.5) +
  #geom_smooth(method="lm", size = 0.5, color = "gray50") +
  labs(title="Binary Search Tree Operations with Logarithmic Regression", x="n", y="Time per Operation (\u03BCs)") +
  theme(plot.title = element_text(hjust=0.5),
        # legend.position = "none",
        panel.spacing = unit(1, "lines"),
        panel.border = element_rect(fill=NA, color="gray90", size=0.5, linetype="solid"),
        panel.background = element_rect(fill = "gray90"),
        panel.grid.minor.x = element_line(size=0.1)) +
  coord_trans(x="log10") +
  ylim(0,5) +
  scale_x_continuous(breaks = scales::trans_breaks("log10", function(x) 10^x),  minor_breaks = log10_minor_break(), labels = scales::trans_format("log10", scales::math_format(10^.x))) +
  facet_grid(. ~ operation)
p_log.double
```

![](SkipListAnalysis_files/figure-markdown_github/Double%20Logarithmic%20Regression-1.png)
