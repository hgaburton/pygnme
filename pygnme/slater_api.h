#ifndef PYGNME_SLATER_API_H_
#define PYGNME_SLATER_API_H_

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

//#include "libgnme/slater/slater_condon.h"
#include "libgnme/slater/slater_rscf.h"
#include "libgnme/slater/slater_uscf.h"

namespace py = pybind11;

//namespace pybind11::literals {

/*
 * Export slater_rscf
 */
template<typename Tc, typename Tf, typename Tb>
void export_slater_rscf(py::module &m, const std::string &typestr) {
    std::string pyclass_name = std::string("slater_rscf_") + typestr;
    using SlaterRscf = libgnme::slater_rscf<Tc, Tf, Tb>;
    py::class_<SlaterRscf>(m, pyclass_name.c_str())
        // Constructors:
        .def(py::init<const size_t, const size_t, const size_t, const arma::Mat<Tb>>())
        .def(py::init<const size_t, const size_t, const size_t, const arma::Mat<Tb>, double>())
        // Functions:
        .def("add_one_body", &SlaterRscf::add_one_body)
        .def("add_two_body", &SlaterRscf::add_two_body)
        .def("evaluate", [](SlaterRscf &scf, 
                            arma::Mat<Tc> &Cx, arma::Mat<Tc> &Cw,
                            Tc &S, Tc &V) {
                scf.evaluate(Cx, Cw, S, V);
                return std::make_tuple(S,V);
             },
             py::arg("Cx"),
             py::arg("Cw"),
             py::arg("S") = 0.0,
             py::arg("V") = 0.0
        )
        .def("evaluate_overlap", [](SlaterRscf &scf,
                                    arma::Mat<Tc> &Cx, arma::Mat<Tc> &Cw,
                                    Tc &S) {
                scf.evaluate_overlap(Cx, Cw, S);
                return std::make_tuple(S);
            },
            py::arg("Cx"),
            py::arg("Cw"),
            py::arg("S") = 0.0
        )
        .def("evaluate_s2", [](SlaterRscf &scf,
                                    arma::Mat<Tc> &Cx, arma::Mat<Tc> &Cw,
                                    Tc &S2) {
                scf.evaluate_s2(Cx, Cw, S2);
                return S2;
            },
            py::arg("Cx"),
            py::arg("Cw"),
            py::arg("S2") = 0.0
        );
}

/*
 * Export slater_uscf
 */
template <typename Tc, typename Tf, typename Tb>
void export_slater_uscf(py::module &m, const std::string &typestr) {
    std::string pyclass_name = std::string("slater_uscf_") + typestr;
    using SlaterUscf = libgnme::slater_uscf<Tc, Tf, Tb>;
    py::class_<SlaterUscf>(m, pyclass_name.c_str())
        // Constructors:
        .def(py::init<const size_t, const size_t, const size_t, const size_t, const arma::Mat<Tb>>())
        .def(py::init<const size_t, const size_t, const size_t, const size_t, const arma::Mat<Tb> , double>())
        // Functions:
        .def("add_one_body", py::overload_cast<arma::Mat<Tf> &>(&SlaterUscf::add_one_body))
        .def("add_one_body", py::overload_cast<arma::Mat<Tf> &, arma::Mat<Tf> &>(&SlaterUscf::add_one_body))
        .def("add_two_body", &SlaterUscf::add_two_body)
        .def("evaluate", [](SlaterUscf &scf, 
                            arma::Mat<Tc> &Cxa, arma::Mat<Tc> &Cxb,
                            arma::Mat<Tc> &Cwa, arma::Mat<Tc> &Cwb,
                            Tc &S, Tc &V) {
                scf.evaluate(Cxa, Cxb, Cwa, Cwb, S, V);
                return std::make_tuple(S,V);
             },
             py::arg("Cxa"),
             py::arg("Cxb"),
             py::arg("Cwa"),
             py::arg("Cwb"),
             py::arg("S") = 0.0,
             py::arg("V") = 0.0
        )
        .def("evaluate_overlap", [](SlaterUscf &scf, 
                            arma::Mat<Tc> &Cxa, arma::Mat<Tc> &Cxb,
                            arma::Mat<Tc> &Cwa, arma::Mat<Tc> &Cwb,
                            Tc &S) {
                scf.evaluate_overlap(Cxa, Cxb, Cwa, Cwb, S);
                return S;
             },
             py::arg("Cxa"),
             py::arg("Cxb"),
             py::arg("Cwa"),
             py::arg("Cwb"),
             py::arg("S") = 0.0
        )
        .def("evaluate_s2", [](SlaterUscf &scf, 
                            arma::Mat<Tc> &Cxa, arma::Mat<Tc> &Cxb,
                            arma::Mat<Tc> &Cwa, arma::Mat<Tc> &Cwb,
                            Tc &S2) {
                scf.evaluate_s2(Cxa, Cxb, Cwa, Cwb, S2);
                return S2;
             },
             py::arg("Cxa"),
             py::arg("Cxb"),
             py::arg("Cwa"),
             py::arg("Cwb"),
             py::arg("S2") = 0.0
        );
}

//} // namespace:pybind11

#endif
