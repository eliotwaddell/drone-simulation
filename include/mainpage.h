/*! \mainpage   CSCI 3081 Delivery Simulation project
*
*\section The The following instructions are meant to be executed on vole2d or vole3d :
*
* To start up the simulation, navigate to the 'project' directory. Once there, run the 'make'
* command. After that, run the command './bin/run.sh' This will begin the connection to the simulation
* webpage but will not start the simulation until you connect to it from a browser. In a new Firefox browser
* window, browse to the page 'http://127.0.0.1:8081/' The simulation will now begin. Use the
* 'Change View' drop down bar to change which entity you will follow during the simualtion.
* Use the simulation speed bar to change how fast the simulation happens. Once the simulation is complete,
* click on the 'Kill Simulation' bar to kill the simulation. To run it again, go back to your terminal and
* reenter the command './bin/run.sh'
*
* To view the tests for the simulation, navigate to the 'project' directory. Once there, run the 'make'
* command to compile the needed files. Next, run the command 'make test' to compile the test files.
* After that, run the command './bin/test.sh' This will run the google tests that test each of the
* files that are used to create the simulation and display the results to you in the terminal.
*
* To generate documentation, first build the project with `make` in the `project` directory.
* Next, navigate to `project/docs` and run `doxygen Doxyfile`.
* Then open `project/docs/html/index.html` in your web browser to view the documentation.
*
*\section Iteration Iteration 2 Final UML:
*
*\image{inline} html Iteration2UML.png width=100%
*
*
*\section   Factory Factory Discussion:
*
* Concrete Factory
*   A concrete factory design pattern is one in which you have a single factory class that is used to
*   create the different objects. These objects are inheriting off of one base class and the factory
*   class must be connected to each of these classes in order to create them.

*   Some advantages of a concrete factory design are legibility and ease of implementation. The legibility
*   of the concrete factory is great because there is only one factory. This design pattern is used
*   when there aren't that many objects that will be created inside the other functions and when
*   new types of objects aren't going to be added to the system. This allows for easy diagramming and
*   use throughout the system because there is a limited number of classes and funcitons. It also
*   allows for easy implementation because the programmer only has to create one factory class that
*   will handle which object to create.

*   A disadvantage of concrete factory design patterns is if the programmer wants to add a new
*   type of object. To do this, the programmer would have to create that new object that inherits
*   off of the base class then, change the main factory class to add this other class's created
*   and link these two new classes together. This is a lot of work to just add a single new object
*   for the system to use.
*
*   This is how the simulation would look as an concrete factory:
* \image{inline} html ConcreteFactory.png width=50%
*
* Abstract Factory
*   An abstract factory design is a factory design in which each different object you wish to create
*   has its own facory that handles the minutia of creating that specific object. The abstract factory
*   controls which of the other factories to call in order to create the desired object
*
*   Some advantages of an abstract factory design are that the main abstract factory doesn't have to
*   implement the individual constructors of each specfic object, it just has to call which factory.
*   This cleans up the main factory of the abstract factory design pattern, and makes implementing new
*   objects for the system much easier. It also makes it easy to implement and use a new object. The
*   object would just need its own factory and then the abstract factory would have to use it. Otherwise,
*   no other classes would need to be changed in order to implement the new object.
*
*   A disadvantage of an abstract factory design is that the abstract factory needs to extend to each
*   of the other factory classes. This makes your total sceme more dependent on each other, making it
*   have high coupling. So if one class changes within the system, multiple have to be edited and fixed.
*
*   This is how the simulation would look as an abstract factory:
* \image{inline} html AbstractFactory.png width=50%
*
* Composite Factory
*
*   An advantage of a composite factory is that the programmer is able to split up the creation of object
*   into their own base forms, making creation as simple as possible. The main composite factory only has
*   to find which other factory to use. That other factory only needs to focus on creating the one object
*   that its designed to produce. Composite factory's make creation and implementation easy for the programmer.
*
*   A disadvantage of the compostie factory design is the high coupling between classes. The main composite
*   factory must contain each factory of the different object types. Also each factory must inherit from the
*   Base factory. This leads to high coupling and will make it difficult to update and implement changes from
*   one object to another.
*
*   This is how the simulation would look as a composite factory:
*\image{inline} html CompositeFactory.png width=50%
*
*\section Which Which Factory is used in the simulation:
*
* 
*
*   To do this, a composite_factory class was created that had drone_factory, customer_factory, and package_factory
*   objects as its attributes. All four of these factory classes inherited from a base class, IEntityFactory that had
*   CreateEntity as a virtual function for all four to implement. The composite_factory implemented
*   CreateEntity by finding the desired type of the entity to be created, and then calling CreateEntity
*   on the specific factory attribute. For example, if the CreateEntity call to composite_factory
*   had drone as its type, then composite_factory would call CreateEntity from the dron_factory attribute
*   in order to return a new drone object. The drone_factory, customer_factory, and the package_factory
*   create their own respective enties when CreateEntity is called on them.
*
*   An advantage of using the composite factory this way is to make it easier to implement in the
*   DeliverySystem class. DeliverSystem only needed to have an attribute composite factory in order
*   to create drones, packages and customers. This made entity creation easy to understand
*   for the programmer and makes implementation simple. It also allows for us to implement new objects
*   into the system simply. All we would have to do is add the new factory and attribute to the composite_factory
*   and the system would be able to create new objects.
*
*   A disadvantage of using the composite factory design pattern is that there is a lot of
*   interconnections between classes. All four factories inherit from the IEntityFactory and the package,
*   drone, and customer factories all are a part of the composite_factory. A small change in one class
*   could lead to changes in many of the surrounding classes due to the relatively high coupling.
*
*
*
*\section Observer Observer Pattern Discussion
*
*   The simulation implements the observer pattern, with the WebSceneViewer and EntityConsoleLogger
*   as the Observers, and the Entities themselves being the subjects. It is implemented through a method
*   that is defined in the EntityBase class, NotifyObservers.
*
*   This method has two options for input, one
*   takes a string for the type of notification the entity is going to broadcast, which so far has always been
*   the standard "notify", and it takes a second string, value, which represents what the notification is for,
*   an example value would be "idle" if an entity goes idle, or "en route" if it starts moving. The method
*   creates a picojson object that formats the notification so it is compatible with the existing observer interface.
*
*   The other variant is for the case that the observer needs the route information of the entity. It does the same
*   thing as the two-parameter method, except it decodes the Vector3D route into a vector of std::vectors, before
*   re-encoding it into a json compatible array that is added to the picojson object and sent to the observer.
*
*
*
* \section Designing Designing and Implementing the different routes
*
* The implementation of the Beeline route for the drone was quite simple. Our Beeline route consisted of the drone moving
* upwards by a constant distance (70) before moving to the point above the destination. It then will move down 70 units to 
* the destination. These points were put into a vector for the drone to follow in order to successfully move along the path.
* 
* The implementation of the parabola was a bit more complicated. This route involved taking the distance between the source 
* and destination and dividing that by, in our case, 100. These 100 points are the points the drone would follow if it were
* to go in a straight line to its destination. To create a parabola, we needed to add some y value to each of the 100 points
* in order for the drone to smoothly fly up and down in an arc. This y value was the result of equation 2 given to us in
* lab: Y = (1 - distance(V, Vm)^2 / distance(Vo, Vm)^2) * j . V is the point the drone will be moving to, Vm is the midpoint,
* Vo is the source point, and j is the max height of the parabola (we chose 200). We then plugged in each of our 100 points into
* this equation, and added the result to the y value of each of those points. These points are then added to the route vector
* (a vector full of points for the drone to travel to). Route will contain the initial drone position, the destination, and 98
* intermediate points. Following the route, the drone will arc up and then back down, hitting the max height of 200 at the vertex,
* halfway to the destination.
* Finally, the implementation of the smart route was mostly provided to us. Using the graph class and an IGraph*, we just needed 
* to call GetPath on the graph instance within DeliverySystem. GetPath utilizes a shortest path algorithm to calculate the best 
* route to take without hitting buildings and returns a vector of points for the drone to follow.  
*
* The diagram here shows the implementation of the strategy pattern of our drone routes:
*\image{inline} html Path.png width=50%
*
* The design pattern we used for the drone to deliver packages is the strategy pattern. This pattern allows us to implement multiple
* routes without having to change the drone or delivery simulation code. To implement this, first we created a class called Path
* that had only 1 virtual method: CreateRoute. Then for each path, we created a new class that inherited off of Path and implemented
* their own version of CreateRoute. After that we created a class called path_context that has a Path object and a method GetPath. 
* When CreatePath is called, path_context interprets the path type specified to create a new instance of one of the children classes
* of Path. Then it uses that child’s CreateRoute method to return the vector of points back to whichever class called it.
*
* The strategy pattern makes it simple and easy to add new routes for the drone to take. Adding a new route is as easy as creating
* a new class that inherits from Path and overrides the CreateRoute method and editing path_context  to recognize the path specified.
* This design pattern adds a lot of flexibility to the Drone and DeliverySimulation classes without changing the code there as well
* as separating the complexities of route creation away from the two classes.
* 
* The challenges our team faced with the design of the strategy pattern was what would the context class be/do and which classes needed
* to use the different paths. Initially, we did not understand if we needed to use the Drone and DeliverySimulation classes as the
* context or if we would need to create a completely new class to act as the context class. To help our understanding, I did some
* research online and found help through the website  https://refactoring.guru/design-patterns/strategy/cpp/example as well as the
* provided website examples on canvas. These resources were helpful in coming to the conclusion that we would need an intermediate
* context class between the paths and the Drone and DeliverySimulation. This context class determines which of the path choices to
* call GetRoute from in order to create the correct path. 
* Some parts of the implementation of our strategy pattern that our team struggled with are the smart route and the parabolic route.
* Our issue with the smart route was how to get the graph into the path in order for us to call GetPath through the proper IGraph*.
* To resolve this, we created SetGraph helpers in the path_context and path class to pass in the graph from the Drone and DeliverySimulation
* classes. This allowed for the correct graph to be used in order to produce the smart route for the Drone to take. The struggle with
* the parabolic route was through Lab 14. We found the provided equations to be confusing and worded a bit funny. To help with our 
* understanding in order to implement this route, we researched parabolic routes and drew sketches. Mapping it out and diagramming
* assisted us in creating the correct equations and a smooth and accurate path. 
*
*\section Teamwork Teamwork Documentation
* First meeting:
* Divided up the work and scheduled intermittent goals, set a goal to try and have the Observer Pattern, Robot, Multiple Packages and
* tests done by April 1, with room left for bug fixes and documentation/code cleaning. This was for the first deliverable due on April 2.
* 
* Second meeting:
* Divided the remaining work for Iteration 2, which amounted to implementing the Strategy Pattern, Battery functionality, as well as tests for
* those. Had a goal to have these finished by April 15, so that the remaining time could be spent on documentation.
*
* Third meeting:
* Parabolic pattern was not working so we met to try and fix it, it appeared to cause the Drone to go in an arbitrary direction. Turns out
* that’s what was happening, because each step just added a scalar value to the Drone’s current position. Switched it to add a vector each 
* step and it worked.
*
* Due to us only having three group members, each team member took on a role and a third. We decided to distribute the load of 
* scheduler amung the three of us. The roles were:
*
* Developmental lead: Joe
*
* Reporter: Jack
*
* Project Manager: Eliot
*
* Scheduler: All
*
* 
*
* General task distribution:
*
* Eliot: Observer Pattern and Battery implementation
*
* Jack: Multiple Packages, Robot, Strategy Pattern
*
* Joe: All testing for all aforementioned features
* 
* Each person contributed sufficiently and equally to the project.




*/
