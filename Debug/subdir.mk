################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../BoundingBox.cc \
../Camera.cc \
../Intersection.cc \
../Materials.cc \
../Plane.cc \
../Point.cc \
../Ray.cc \
../Sphere.cc \
../Triangle.cc \
../Vector.cc \
../light.cc \
../readscene.cc 

OBJS += \
./BoundingBox.o \
./Camera.o \
./Intersection.o \
./Materials.o \
./Plane.o \
./Point.o \
./Ray.o \
./Sphere.o \
./Triangle.o \
./Vector.o \
./light.o \
./readscene.o 

CC_DEPS += \
./BoundingBox.d \
./Camera.d \
./Intersection.d \
./Materials.d \
./Plane.d \
./Point.d \
./Ray.d \
./Sphere.d \
./Triangle.d \
./Vector.d \
./light.d \
./readscene.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/OpenEXR -I. -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


