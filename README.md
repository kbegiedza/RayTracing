# RayTracing

[![Build Status](https://dev.azure.com/bloodstoneteam/BloodstoneEngine/_apis/build/status/Ursanon.RayTracing?branchName=master)](https://dev.azure.com/bloodstoneteam/BloodstoneEngine/_build/latest?definitionId=1&branchName=master)
![GitHub](https://img.shields.io/github/license/Ursanon/RayTracing)
![GitHub issues](https://img.shields.io/github/issues/Ursanon/RayTracing)

Simple raytracer implementation with:

* sphere geometry
* 3 materials (diffuse, metallic, refractive)
* hardcoded demo-world
* naive arguments parser
* ppm exporter
* tons of math

Produces `.ppm` file with rendered camera's view.

## How to build?

Use `CMake`.

## How to use?

`<executable> 🅐 🅑 🅒 🅓 🅔`  
where:  
`🅐` - render width  
`🅑` - render height  
`🅒` - smoothing samples (anty-aliasing)
`🅓` - aperture of camera's lens
`🅔` - output path
