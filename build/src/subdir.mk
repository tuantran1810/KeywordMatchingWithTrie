################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
CPP_SRCS += \
../src/keywordMatcher.cpp \
../src/keywordMatchingRunner.cpp \
../src/trie.cpp \
../src/utils.cpp

OBJS += \
./src/keywordMatcher.o \
./src/keywordMatchingRunner.o \
./src/trie.o \
./src/utils.o

CPP_DEPS += \
./src/keywordMatcher.d \
./src/keywordMatchingRunner.d \
./src/trie.d \
./src/utils.d


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"../inc" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


