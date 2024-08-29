#include <hector_math/helpers/coloring.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace hector_math;

PYBIND11_MODULE( impl, m )
{
  auto coloring = m.def_submodule( "coloring", "Coloring helpers for visualization." );
  py::class_<coloring::RGB>( coloring, "RGB" )
      .def_readwrite( "r", &coloring::RGB::r )
      .def_readwrite( "g", &coloring::RGB::g )
      .def_readwrite( "b", &coloring::RGB::b )
      .def( "toRGBf", &coloring::RGB::toRGBf, "Convert to RGBf." )
      .def( "toRGBA", &coloring::RGB::toRGBA, "Convert to RGBA." )
      .def( py::pickle( []( const coloring::RGB &c ) { return py::make_tuple( c.r, c.g, c.b ); },
                        []( const py::tuple &t ) {
                          if ( t.size() != 3 )
                            throw std::runtime_error( "Invalid state!" );
                          return coloring::RGB( t[0].cast<unsigned char>(),
                                                t[1].cast<unsigned char>(),
                                                t[2].cast<unsigned char>() );
                        } ) )
      .def( "__repr__", []( const coloring::RGB &c ) {
        return "<RGB: " + std::to_string( c.r ) + ", " + std::to_string( c.g ) + ", " +
               std::to_string( c.b ) + ">";
      } );
  py::class_<coloring::RGBA>( coloring, "RGBA" )
      .def_readwrite( "r", &coloring::RGBA::r )
      .def_readwrite( "g", &coloring::RGBA::g )
      .def_readwrite( "b", &coloring::RGBA::b )
      .def_readwrite( "a", &coloring::RGBA::a )
      .def( "toRGBAf", &coloring::RGBA::toRGBAf, "Convert to RGBAf." )
      .def( py::pickle(
          []( const coloring::RGBA &c ) { return py::make_tuple( c.r, c.g, c.b, c.a ); },
          []( const py::tuple &t ) {
            if ( t.size() != 4 )
              throw std::runtime_error( "Invalid state!" );
            return coloring::RGBA( t[0].cast<unsigned char>(), t[1].cast<unsigned char>(),
                                   t[2].cast<unsigned char>(), t[3].cast<unsigned char>() );
          } ) )
      .def( "__repr__", []( const coloring::RGBA &c ) {
        return "<RGBA: " + std::to_string( c.r ) + ", " + std::to_string( c.g ) + ", " +
               std::to_string( c.b ) + ", " + std::to_string( c.a ) + ">";
      } );
  py::class_<coloring::RGBf>( coloring, "RGBf" )
      .def_readwrite( "r", &coloring::RGBf::r )
      .def_readwrite( "g", &coloring::RGBf::g )
      .def_readwrite( "b", &coloring::RGBf::b )
      .def( "toRGB", &coloring::RGBf::toRGB, "Convert to RGB." )
      .def( "toRGBAf", &coloring::RGBf::toRGBAf, "Convert to RGBAf." )
      .def( py::pickle( []( const coloring::RGBf &c ) { return py::make_tuple( c.r, c.g, c.b ); },
                        []( const py::tuple &t ) {
                          if ( t.size() != 3 )
                            throw std::runtime_error( "Invalid state!" );
                          return coloring::RGBf( t[0].cast<float>(), t[1].cast<float>(),
                                                 t[2].cast<float>() );
                        } ) )
      .def( "__repr__", []( const coloring::RGBf &c ) {
        return "<RGBf: " + std::to_string( c.r ) + ", " + std::to_string( c.g ) + ", " +
               std::to_string( c.b ) + ">";
      } );
  py::class_<coloring::RGBAf>( coloring, "RGBAf" )
      .def_readwrite( "r", &coloring::RGBAf::r )
      .def_readwrite( "g", &coloring::RGBAf::g )
      .def_readwrite( "b", &coloring::RGBAf::b )
      .def( "toRGBA", &coloring::RGBAf::toRGBA, "Convert to RGBA." )
      .def( py::pickle(
          []( const coloring::RGBAf &c ) { return py::make_tuple( c.r, c.g, c.b, c.a ); },
          []( const py::tuple &t ) {
            if ( t.size() != 4 )
              throw std::runtime_error( "Invalid state!" );
            return coloring::RGBAf( t[0].cast<float>(), t[1].cast<float>(), t[2].cast<float>(),
                                    t[3].cast<float>() );
          } ) )
      .def( "__repr__", []( const coloring::RGBAf &c ) {
        return "<RGBAf: " + std::to_string( c.r ) + ", " + std::to_string( c.g ) + ", " +
               std::to_string( c.b ) + ", " + std::to_string( c.a ) + ">";
      } );
  ;
  py::enum_<coloring::GradientMethod>( coloring, "GradientMethod" )
      .value( "Grayscale", coloring::GradientMethod::Grayscale )
      .value( "Blue2Red", coloring::GradientMethod::Blue2Red )
      .value( "Red2Blue", coloring::GradientMethod::Red2Blue )
      .value( "Turbo", coloring::GradientMethod::Turbo )
      .value( "Civides", coloring::GradientMethod::Civides );
  coloring.attr( "NUM_SEGMENT_COLORS" ) = coloring::NUM_SEGMENT_COLORS;

  coloring.def( "segment_color", &coloring::segmentColor,
                "Get a distinct color for a color segment." );
  coloring.def(
      "gradient_color",
      py::overload_cast<float, float, float, coloring::GradientMethod>( &coloring::gradientColor ),
      py::arg( "value" ), py::arg( "min" ) = 0.0f, py::arg( "max" ) = 1.0f,
      py::arg( "method" ) = coloring::GradientMethod::Turbo, "Get a color from a gradient." );
}
