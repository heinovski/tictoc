require(ggplot2)

d <- read.delim('a.csv')

p <- ggplot(d) + stat_ecdf(aes(x=hops, color=node)) + coord_cartesian(xlim = c(0,50)) + theme_bw()
print(p)
ggsave("a.pdf", p)


