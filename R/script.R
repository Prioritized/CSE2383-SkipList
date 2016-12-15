library(ggplot2)
library(scales)

df <- read.csv("../data/timing_results.csv")

df.sl <- subset(df, structure == "skip list")
df.bst <- subset(df, structure == "binary tree")
df.ll <- subset(df, structure == "linked list")
df.double <- rbind(df.sl, df.bst)


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


# skip list
#png(height = 1200, width = 2600, filename = "plot_sl_log.png", type = "cairo", res = 400)
p_log.sl <- ggplot(data=df.sl, aes(n, tpo, color = operation)) +
  geom_point(size = 1) +
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

Rsq_log(df.sl)

#png(height = 1200, width = 2600, filename = "plot_sl_lin.png", type = "cairo", res = 400)
p_linear.sl <- ggplot(data=df.sl, aes(n / 10^6, tpo, color = operation)) +
  geom_point(size = 1) +
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

Rsq_lin(df.sl)

# binary search tree
#png(height = 1200, width = 2600, filename = "plot_bst_log.png", type = "cairo", res = 400)
p_log.bst <- ggplot(data=df.bst, aes(n, tpo, color = operation)) +
  geom_point(size = 1) +
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

Rsq_log(df.bst)

#png(height = 1200, width = 2600, filename = "plot_bst_lin.png", type = "cairo", res = 400)
p_linear.bst <- ggplot(data=df.bst, aes(n / 10^6, tpo, color = operation)) +
  geom_point(size = 1) +
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

Rsq_lin(df.bst)

# linked list
#png(height = 1200, width = 2600, filename = "plot_ll_log.png", type = "cairo", res = 400)
p_log.ll <- ggplot(data=df.ll, aes(n, tpo, color = operation)) +
  geom_point(size = 1) +
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

Rsq_log(df.ll)

#png(height = 1200, width = 2600, filename = "plot_ll_lin.png", type = "cairo", res = 400)
p_linear.ll <- ggplot(data=df.ll, aes(n / 10^4, tpo, color = operation)) +
  geom_point(size = 1) +
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

Rsq_lin(df.ll)


# skip list and binary search tree for direct comparison
#png(height = 1200, width = 2600, filename = "plot_double_log.png", type = "cairo", res = 400)
p_log.double <- ggplot(data=df.double, aes(n, tpo, color = structure)) +
  geom_point(size = 1) +
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


# combine logarithmic and linear plots into one if need be...
#grid.arrange(p_log.sl, p_linear.sl, ncol=1, top=textGrob("Skip List", gp=gpar(fontsize=15,font=1)))
#grid.arrange(p_log.bst, p_linear.bst, ncol=1, top=textGrob("Binary Search Tree", gp=gpar(fontsize=15,font=1)))
