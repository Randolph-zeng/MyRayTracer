EXENAME = drawimage
EXENAME2 = testimage
OBJS =  png.o ViewPlane.o rgbapixel.o Matrix.o Vector3D.o Point2D.o Point3D.o Ray.o Normal.o ShadeRec.o Tracer.o Whitted.o Material.o  GeometricObject.o Sphere.o Plane.o Triangle.o Light.o PointLight.o Ambient.o Pinhole.o Camera.o BRDF.o Lambertian.o GlossySpecular.o Matte.o Sampler.o MultiJittered.o BVH.o BBox.o World.o DrawImage.o 
OBJS2 = drawimage.o 


CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O3 -mssse3  -o 
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -mssse3

$(EXENAME) : $(OBJS) 
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXENAME)

$(EXENAME2) : $(OBJS2) 
	$(LD) $(LDFLAGS) $(OBJS)  -o $(EXENAME2)

drawimage.o : DrawImage.cpp png.cpp Viewplane.cpp Matrix.cpp rgbapixel.cpp Vector3D.cpp Point3D.cpp Point2D.cpp Ray.cpp Normal.cpp Tracer.cpp Whitted.cpp ShadeRec.cpp GeometricObject.cpp Sphere.cpp Plane.cpp Triangle.cpp Light.cpp PointLight.cpp Ambient.cpp Camera.cpp Pinhole.cpp Material.cpp Matte.cpp Sampler.cpp MultiJittered.cpp BRDF.cpp Lambertian.cpp GlossySpecular.cpp BBox.cpp BVH.cpp Log.h Stopwatch.h IntersectionInfo.h World.cpp 
	$(CXX) $(CXXFLAGS) DrawImage.cpp

testimage.o : testimage.cpp  image.o rgbapixel.o png.o 
	$(CXX) $(CXXFLAGS) testimage.cpp

all: drawimage

clean :
	-rm -f *.o $(EXENAME) $(EXENAME2)