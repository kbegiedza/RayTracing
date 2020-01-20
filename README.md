# RayTracing

[![Build Status](https://dev.azure.com/bloodstoneteam/BloodstoneEngine/_apis/build/status/Ursanon.RayTracing?branchName=master)](https://dev.azure.com/bloodstoneteam/BloodstoneEngine/_build/latest?definitionId=1&branchName=master)
![GitHub](https://img.shields.io/github/license/Ursanon/RayTracing)
![GitHub issues](https://img.shields.io/github/issues/Ursanon/RayTracing)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/f045f5190a6b44c28a2e2a8754650f77)](https://www.codacy.com/manual/Ursanon/RayTracing?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Ursanon/RayTracing&amp;utm_campaign=Badge_Grade)

Simple raytracer implementation with:

*   sphere geometry
*   3 materials (diffuse, metallic, refractive)
*   hardcoded demo-world
*   naive arguments parser
*   ppm exporter
*   tons of math

Produces `.ppm` file with rendered camera's view.

## How to build

Use `CMake`.

## How to use

Run: `<executable> 🅐 🅑 🅒 🅓 🅔`

where:    
`🅐` - render width    
`🅑` - render height    
`🅒` - smoothing samples (anty-aliasing)    
`🅓` - aperture of camera's lens    
`🅔` - output path    

## Example output

Used params: `🅐=1920 🅑=1080 🅒=100 🅓=0.15`    
<img src="https://github.com/Ursanon/RayTracing/blob/master/resources/example_0.png" width="320">
