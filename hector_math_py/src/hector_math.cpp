#include <pybind11/pybind11.h>
#include <hector_math/helpers/coloring.hpp>

namespace py = pybind11;
using namespace hector_math;

PYBIND11_MODULE(module, m) {
    auto coloring = m.def_submodule("coloring", "Coloring helpers for visualization.");
    py::class_<coloring::RGB>(coloring, "RGB")
            .def_readwrite("r", &coloring::RGB::r)
            .def_readwrite("g", &coloring::RGB::g).def_readwrite("b", &coloring::RGB::b)
            .def("toRGBf", &coloring::RGB::toRGBf, "Convert to RGBf.")
            .def(py::pickle(
                [](const coloring::RGB &c) {
                    return py::make_tuple(c.r, c.g, c.b);
                }, [](const py::tuple &t) {
                    if (t.size() != 3) throw std::runtime_error("Invalid state!");
                    return coloring::RGB(t[0].cast<unsigned char>(), t[1].cast<unsigned char>(),
                                         t[2].cast<unsigned char>());
                }))
            .def("__repr__", [](const coloring::RGB &c) {
                return "<RGB: " + std::to_string(c.r) + ", " + std::to_string(c.g) + ", " + std::to_string(c.b) + ">";
            });
    py::class_<coloring::RGBf>(coloring, "RGBf")
            .def_readwrite("r", &coloring::RGBf::r)
            .def_readwrite("g", &coloring::RGBf::g)
            .def_readwrite("b", &coloring::RGBf::b)
            .def("toRGB", &coloring::RGBf::toRGB, "Convert to RGB.")
            .def(py::pickle(
                [](const coloring::RGBf &c) {
                    return py::make_tuple(c.r, c.g, c.b);
                }, [](const py::tuple &t) {
                    if (t.size() != 3) throw std::runtime_error("Invalid state!");
                    return coloring::RGBf(t[0].cast<float>(), t[1].cast<float>(), t[2].cast<float>());
                }))
            .def("__repr__", [](const coloring::RGB &c) {
                return "<RGBf: " + std::to_string(c.r) + ", " + std::to_string(c.g) + ", " + std::to_string(c.b) + ">";
            });;
    py::enum_<coloring::GradientMethod>(coloring, "GradientMethod")
            .value("Grayscale", coloring::GradientMethod::Grayscale)
            .value("Blue2Red", coloring::GradientMethod::Blue2Red)
            .value("Red2Blue", coloring::GradientMethod::Red2Blue)
            .value("Turbo", coloring::GradientMethod::Turbo)
            .value("Civides", coloring::GradientMethod::Civides);
    coloring.attr("NUM_SEGMENT_COLORS") = coloring::NUM_SEGMENT_COLORS;

    coloring.def("segment_color", &coloring::segmentColor, "Get a distinct color for a color segment.");
    coloring.def("gradient_color",
                 py::overload_cast<float, float, float,
                     coloring::GradientMethod>(&coloring::gradientColor),
                 py::arg("value"), py::arg("min") = 0.0f, py::arg("max") = 1.0f,
                 py::arg("method") = coloring::GradientMethod::Turbo, "Get a color from a gradient.");
}
