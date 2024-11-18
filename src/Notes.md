# CAT internal organization

## Graphics and data objects
ciao **cat**::_pippo_

Main namespace is
`cat::` 


Main object for being drawn
`drawable`
has members
`draw`

`drawable`->`ui`->`button`

`drawable`->`gp`->`line`


`streamable`->`gp`->`line`

### Data Structures
Data Structures (DS) derives from the `cat::ds::abstract` abstract object, and contains all the different type of data objects used (pixels, clusters layers, etc...)

`cat::co`->`cat::streamable`->`cat::ds::abstract`

### Graphics Primitives
Graphic Primitives (GP) represents drawable objects in the 3D world of a scene, which is a container GP..

`cat::co`->`cat::streamable`->`cat::drawable`->`cat::gp::abstract`

### User Interfaces
User Interfaces (UI) objects show and allow to modify specific data structures elements within the server graphics interface

`cat::co`->`cat::streamable`->`cat::drawable`->`cat::interface`->`cat::ui::abstract`


```
quoted

```

Ciao~pollo~