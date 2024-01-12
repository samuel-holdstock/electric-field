library(Rcpp)
library(ggplot2)
library(ggnewscale)

sourceCpp("/home/holdstos/Downloads/PhD/Extra-Code/Fields/connector.cpp")

m = data.frame(start())
m = na.omit(m)
l = (sqrt(m$X3^2+m$X4^2))*8
charges = data.frame(get_charges())


ggplot(m,aes(x=X1,y=X2))+
    geom_segment(aes(xend=X1+X3/l,yend=X2+X4/l,colour=l), arrow = arrow(length = unit(0.1, "cm")),size=0.25)+
    scale_colour_continuous(low = "grey80", high = "darkred")+
    new_scale_colour()+
    geom_point(data=charges,aes(x=X1,y=X2,colour=X3))+
    scale_colour_continuous(low="blue",high="red")
