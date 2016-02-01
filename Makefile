EXENAME = drawimage
EXENAME2 = testimage
OBJS =  png.o ViewPlane.o rgbapixel.o Matrix.o Vector3D.o Point3D.o Ray.o Normal.o ShadeRec.o Tracer.o MultipleObjects.o GeometricObject.o Sphere.o Plane.o World.o Triangle.o DrawImage.o 
OBJS2 = png.o image.o rgbapixel.o testimage.o 


CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi



$(EXENAME) : $(OBJS) 
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXENAME)

$(EXENAME2) : $(OBJS2) 
	$(LD) $(LDFLAGS) $(OBJS)  -o $(EXENAME2)

viewplane.o : ViewPlane.cpp ViewPlane.h 
	 $(CXX) $(CXXFLAGS) ViewPlane.cpp

png.o : png.cpp png.h rgbapixel.h  
	$(CXX) $(CXXFLAGS) png.cpp

matrix.o : Matrix.cpp Matrix.h
	$(CXX) $(CXXFLAGS) Matrix.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp
	
vector3d.o : Vector3D.cpp Vector3D.h Matrix.h  
	$(CXX) $(CXXFLAGS) Vector3D.cpp
	
point3d.o : Point3D.cpp Point3D.h Vector3D.h  Matrix.h
	$(CXX) $(CXXFLAGS) Point3D.cpp

ray.o : Ray.cpp Ray.h Vector3D.h Point3D.h
	$(CXX) $(CXXFLAGS) Ray.cpp

normal.o : Normal.cpp Normal.h Vector3D.h Point3D.h Matrix.h  
	$(CXX) $(CXXFLAGS) Normal.cpp

tracer.o : Tracer.cpp Tracer.h Constants.h rgbapixel.h Ray.h World.h 
	$(CXX) $(CXXFLAGS) Tracer.cpp

MultipleObjects.o : MultipleObjects.cpp MultipleObjects.h Tracer.h ShadeRec.h 
	$(CXX) $(CXXFLAGS) MultipleObjects.cpp

GeometricObject.o : GeometricObject.h GeometricObject.cpp rgbapixel.h Point3D.h Normal.h Ray.h ShadeRec.h Constants.h
	$(CXX) $(CXXFLAGS) GeometricObject.cpp

sphere.o : Sphere.cpp Sphere.h GeometricObject.h
	$(CXX) $(CXXFLAGS) Sphere.cpp

plane.o : Plane.cpp Plane.h GeometricObject.h
	$(CXX) $(CXXFLAGS) Plane.cpp

Triangle.o : Triangle.cpp Triangle.h GeometricObject.h
	$(CXX) $(CXXFLAGS) Triangle.cpp
	
shaderec.o : ShadeRec.cpp ShadeRec.h rgbapixel.h Normal.h Point3D.h  
	$(CXX) $(CXXFLAGS) ShadeRec.cpp	

world.o : Ray.h Tracer.h MultipleObjects.h GeometricObject.h Sphere.h Plane.h ViewPlane.h rgbapixel.h png.h Constants.h Matrix.h Vector3D.h Point3D.h Normal.h ShadeRec.h Maths.h World.cpp World.h
	$(CXX) $(CXXFLAGS) World.cpp	

drawimage.o : DrawImage.cpp png.o viewplane.o matrix.o rgbapixel.o vector3d.o point3d.o ray.o normal.o shaderec.o tracer.o MultipleObjects.o GeometricObject.o sphere.o plane.o Triangle.o world.o 
	$(CXX) $(CXXFLAGS) DrawImage.cpp

testimage.o : testimage.cpp  image.o rgbapixel.o png.o 
	$(CXX) $(CXXFLAGS) testimage.cpp

all: testimage testscene

clean :
	-rm -f *.o $(EXENAME) $(EXENAME2)