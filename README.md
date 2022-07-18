# RocketGround
A highly configurable gui for displaying rocketry flight data, and sending commands

## About
A Ground control gui designed to be compatible with a wide variety of devices by using a rest api structure

Data is pulled and displayed via api endpoint, and commands are sent via api endpoint, meaning, with the creation of
a middle-layer api, the majority of systems can be interfaced with this gui

## Current use cases
Currently this system is being developed to act as a pre-launch / testing interface for model rocketry.

The rockets main computer is a raspberry pi which hosts an adhock network and an api, that contains data from all onboard sensors

The user can connect to the hosted adhock and configure RocketGround to look for data on defined endpoints, and configure the buttons to
control arming, test-modes, and e-match ignition

## Usage
Currently, RocketGround is still in development, the source files can be downloaded and setup using QT Creator

An official release will be compiled once I am happy with the overal layout and set of base features
