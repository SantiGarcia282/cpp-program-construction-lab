# Group Mini Proposal

**Group:** \[group name or number]  
**Team members:** Santiago García Frutos, Hammi Hussein, Altun Nahidi, Max Raneheim
**Repository:** https://github.com/SantiGarcia282/cpp-program-construction-lab

## Working title

The Goalkeeper Minigame

## Interaction in one sentence

Moving a physical marker laterally in front of the camera controls digital goalkeeper gloves on the screen to block incoming virtual shots.

## Physical marker action

What will the user do with the marker?

* Move it quickly left and right (horizontal axis) across the camera's field of view to simulate a goalkeeper's lateral movement.

## Application response

What will change in the application?

* The horizontal position of the physical marker translates directly to the X-axis position of a digital object (goalkeeper gloves) within a simple 2D defensive simulation

## Minimum demonstrable version

The system reliably tracks the marker's X-axis movement without significant lag, allowing the user to successfully move the gloves and intercept basic targets (balls) coming from the top of the screen.

## Optional extension

Tracking the marker's Y-axis movement (moving it up and down) alongside the X-axis to allow for a full range of motion, enabling both high and low saves.

## Why this interaction?

It leverages intuitive, fast-paced lateral movements that are natural to a goalkeeper's reflexes. This creates a very clear, immediate, and engaging relationship between the physical action and the digital response, making it easy to test for reliability.

## Current question

What is the most recommended OpenCV function or method in C++ to maintain robust tracking of a marker that is moving very quickly, to prevent losing it due to camera motion blur?

