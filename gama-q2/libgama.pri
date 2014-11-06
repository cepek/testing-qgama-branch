!exists($$LIBGAMASRC) {
  error("GNU Gama project is missing in subdirectory $$LIBGAMASRC")
}

INCLUDEPATH += $$LIBGAMASRC/lib

HEADERS += \
$$LIBGAMASRC/lib/gnu_gama/e3.h \
$$LIBGAMASRC/lib/gnu_gama/ellipsoid.h \
$$LIBGAMASRC/lib/gnu_gama/ellipsoids.h \
$$LIBGAMASRC/lib/gnu_gama/exception.h \
$$LIBGAMASRC/lib/gnu_gama/gon2deg.h \
$$LIBGAMASRC/lib/gnu_gama/intfloat.h \
$$LIBGAMASRC/lib/gnu_gama/latlong.h \
$$LIBGAMASRC/lib/gnu_gama/list.h \
$$LIBGAMASRC/lib/gnu_gama/model.h \
$$LIBGAMASRC/lib/gnu_gama/movetofront.h \
$$LIBGAMASRC/lib/gnu_gama/obsdata.h \
$$LIBGAMASRC/lib/gnu_gama/outstream.h \
$$LIBGAMASRC/lib/gnu_gama/pointbase.h \
$$LIBGAMASRC/lib/gnu_gama/radian.h \
$$LIBGAMASRC/lib/gnu_gama/rand.h \
$$LIBGAMASRC/lib/gnu_gama/statan.h \
$$LIBGAMASRC/lib/gnu_gama/utf8.h \
$$LIBGAMASRC/lib/gnu_gama/version.h \
$$LIBGAMASRC/lib/gnu_gama/visitor.h \
$$LIBGAMASRC/lib/gnu_gama/xml_expat.h \

HEADERS += \
$$LIBGAMASRC/lib/gnu_gama/adj/adj_basefull.h \
$$LIBGAMASRC/lib/gnu_gama/adj/adj_base.h \
$$LIBGAMASRC/lib/gnu_gama/adj/adj_basesparse.h \
$$LIBGAMASRC/lib/gnu_gama/adj/adj_chol.h \
$$LIBGAMASRC/lib/gnu_gama/adj/adj_chol_implementation.h \
$$LIBGAMASRC/lib/gnu_gama/adj/adj_envelope.h \
$$LIBGAMASRC/lib/gnu_gama/adj/adj_envelope_implementation.h \
$$LIBGAMASRC/lib/gnu_gama/adj/adj_gso.h \
$$LIBGAMASRC/lib/gnu_gama/adj/adj.h \
$$LIBGAMASRC/lib/gnu_gama/adj/adj_svd.h \
$$LIBGAMASRC/lib/gnu_gama/adj/envelope.h \
$$LIBGAMASRC/lib/gnu_gama/adj/homogenization.h \

HEADERS += \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_adjres.h \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_cluster.h \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_model.h \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_observation.h \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_parameter.h \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_point.h \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_write_observation_xml.h \

HEADERS += \
$$LIBGAMASRC/lib/gnu_gama/local/acord.h \
$$LIBGAMASRC/lib/gnu_gama/local/angobs.h \
$$LIBGAMASRC/lib/gnu_gama/local/bpoint.h \
$$LIBGAMASRC/lib/gnu_gama/local/c_api.h \
$$LIBGAMASRC/lib/gnu_gama/local/cluster.h \
$$LIBGAMASRC/lib/gnu_gama/local/exception.h \
$$LIBGAMASRC/lib/gnu_gama/local/float.h \
$$LIBGAMASRC/lib/gnu_gama/local/gamadata.h \
$$LIBGAMASRC/lib/gnu_gama/local/html.h \
$$LIBGAMASRC/lib/gnu_gama/local/itstream.h \
$$LIBGAMASRC/lib/gnu_gama/local/language.h \
$$LIBGAMASRC/lib/gnu_gama/local/lcoords.h \
$$LIBGAMASRC/lib/gnu_gama/local/linearization.h \
$$LIBGAMASRC/lib/gnu_gama/local/local_linearization.h \
$$LIBGAMASRC/lib/gnu_gama/local/local_revision.h \
$$LIBGAMASRC/lib/gnu_gama/local/localnetwork2sql.h \
$$LIBGAMASRC/lib/gnu_gama/local/lpoint.h \
$$LIBGAMASRC/lib/gnu_gama/local/matvec.h \
$$LIBGAMASRC/lib/gnu_gama/local/medianf.h \
$$LIBGAMASRC/lib/gnu_gama/local/network_chol.h \
$$LIBGAMASRC/lib/gnu_gama/local/network_env.h \
$$LIBGAMASRC/lib/gnu_gama/local/network_gso.h \
$$LIBGAMASRC/lib/gnu_gama/local/network.h \
$$LIBGAMASRC/lib/gnu_gama/local/network_svd.h \
$$LIBGAMASRC/lib/gnu_gama/local/observation.h \
$$LIBGAMASRC/lib/gnu_gama/local/orientation.h \
$$LIBGAMASRC/lib/gnu_gama/local/pointid.h \
$$LIBGAMASRC/lib/gnu_gama/local/readsabw.h \
$$LIBGAMASRC/lib/gnu_gama/local/revision.h \
$$LIBGAMASRC/lib/gnu_gama/local/skipcomm.h \
$$LIBGAMASRC/lib/gnu_gama/local/sqlitereader.h \
$$LIBGAMASRC/lib/gnu_gama/local/svg.h \
$$LIBGAMASRC/lib/gnu_gama/local/test_linearization_visitor.h \
$$LIBGAMASRC/lib/gnu_gama/local/writevisitor.h \
$$LIBGAMASRC/lib/gnu_gama/local/xmlerror.h \

HEADERS += \
$$LIBGAMASRC/lib/gnu_gama/local/acord/approx_heights.h \
$$LIBGAMASRC/lib/gnu_gama/local/acord/approx_vectors.h \
$$LIBGAMASRC/lib/gnu_gama/local/acord/reduce_observations.h \
$$LIBGAMASRC/lib/gnu_gama/local/acord/reduce_to_ellipsoid.h \

HEADERS += \
$$LIBGAMASRC/lib/gnu_gama/local/pobs/bearing.h \
$$LIBGAMASRC/lib/gnu_gama/local/pobs/format.h \

HEADERS += \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/adjusted_observations.h \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/adjusted_unknowns.h \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/approximate_coordinates.h \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/error_ellipses.h \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/fixed_points.h \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/general_parameters.h \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/network_description.h \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/outlying_abs_terms.h \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/reduced_observations.h \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/reduced_observations_to_ellipsoid.h \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/residuals_observations.h \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/underline.h \

HEADERS += \
$$LIBGAMASRC/lib/gnu_gama/local/median/g2d_cogo.h \
$$LIBGAMASRC/lib/gnu_gama/local/median/g2d_coordinates.h \
$$LIBGAMASRC/lib/gnu_gama/local/median/g2d_exception.h \
$$LIBGAMASRC/lib/gnu_gama/local/median/g2d_helper.h \
$$LIBGAMASRC/lib/gnu_gama/local/median/g2d_point.h \

HEADERS += \
$$LIBGAMASRC/lib/gnu_gama/sparse/intlist.h \
$$LIBGAMASRC/lib/gnu_gama/sparse/sbdiagonal.h \
$$LIBGAMASRC/lib/gnu_gama/sparse/smatrix_graph_connected.h \
$$LIBGAMASRC/lib/gnu_gama/sparse/smatrix_graph.h \
$$LIBGAMASRC/lib/gnu_gama/sparse/smatrix.h \
$$LIBGAMASRC/lib/gnu_gama/sparse/smatrix_ordering.h \
$$LIBGAMASRC/lib/gnu_gama/sparse/svector.h \

HEADERS += \
$$LIBGAMASRC/lib/gnu_gama/xml/baseparser.h \
$$LIBGAMASRC/lib/gnu_gama/xml/dataobject.h \
$$LIBGAMASRC/lib/gnu_gama/xml/dataparser.h \
$$LIBGAMASRC/lib/gnu_gama/xml/encoding.h \
$$LIBGAMASRC/lib/gnu_gama/xml/gkfparser.h \
$$LIBGAMASRC/lib/gnu_gama/xml/htmlparser.h \
$$LIBGAMASRC/lib/gnu_gama/xml/localnetwork_adjustment_results.h \
$$LIBGAMASRC/lib/gnu_gama/xml/localnetwork_adjustment_results_data.h \
$$LIBGAMASRC/lib/gnu_gama/xml/localnetworksql.h \
$$LIBGAMASRC/lib/gnu_gama/xml/localnetworkxml.h \

# matvec

HEADERS += \
$$LIBGAMASRC/lib/matvec/array.h \
$$LIBGAMASRC/lib/matvec/bandmat.h \
$$LIBGAMASRC/lib/matvec/choldec.h \
$$LIBGAMASRC/lib/matvec/covmat.h \
$$LIBGAMASRC/lib/matvec/gso.h \
$$LIBGAMASRC/lib/matvec/hilbert.h \
$$LIBGAMASRC/lib/matvec/inderr.h \
$$LIBGAMASRC/lib/matvec/jacobian.h \
$$LIBGAMASRC/lib/matvec/matbase.h \
$$LIBGAMASRC/lib/matvec/mat.h \
$$LIBGAMASRC/lib/matvec/matvecbase.h \
$$LIBGAMASRC/lib/matvec/matvec.h \
$$LIBGAMASRC/lib/matvec/memrep.h \
$$LIBGAMASRC/lib/matvec/pinv.h \
$$LIBGAMASRC/lib/matvec/sortvec.h \
$$LIBGAMASRC/lib/matvec/svd.h \
$$LIBGAMASRC/lib/matvec/symmat.h \
$$LIBGAMASRC/lib/matvec/transmat.h \
$$LIBGAMASRC/lib/matvec/transvec.h \
$$LIBGAMASRC/lib/matvec/vecbase.h \
$$LIBGAMASRC/lib/matvec/vec.h


SOURCES +=  \
$$LIBGAMASRC/lib/gnu_gama/adj/adj.cpp \
$$LIBGAMASRC/lib/gnu_gama/e3.cpp \
$$LIBGAMASRC/lib/gnu_gama/ellipsoid.cpp \
$$LIBGAMASRC/lib/gnu_gama/ellipsoids.cpp \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_adjres.cpp \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_cluster.cpp \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_model.cpp \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_model_init.cpp \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_model_linearization.cpp \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_model_revision.cpp \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_model_write_xml_adjustment_results.cpp \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_point.cpp \
$$LIBGAMASRC/lib/gnu_gama/g3/g3_write_observation_xml.cpp \
$$LIBGAMASRC/lib/gnu_gama/gon2deg.cpp \
$$LIBGAMASRC/lib/gnu_gama/latlong.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/acord/approx_heights.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/acord/approx_vectors.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/acord.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/acord/reduce_observations.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/acord/reduce_to_ellipsoid.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/gamadata.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/html.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/language.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/localnetwork2sql.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/median/g2d_cogo.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/median/g2d_coordinates.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/median/g2d_helper.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/median/g2d_point.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/network.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/observation.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/observation_local.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/orientation.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/pobs/format.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/pobs/write.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/pointid.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/results/text/underline.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/skipcomm.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/sqlitereader.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/svg.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/test_linearization_visitor.cpp \
$$LIBGAMASRC/lib/gnu_gama/local/xmlerror.cpp \
$$LIBGAMASRC/lib/gnu_gama/outstream.cpp \
$$LIBGAMASRC/lib/gnu_gama/rand.cpp \
$$LIBGAMASRC/lib/gnu_gama/statan.cpp \
$$LIBGAMASRC/lib/gnu_gama/utf8.cpp \
$$LIBGAMASRC/lib/gnu_gama/version.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/baseparser.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/dataobject.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/dataparser_adj.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/dataparser.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/dataparser_g3adj.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/dataparser_g3.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/encoding_cp1251.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/encoding.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/encoding_unknown_handler.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/gkfparser.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/htmlparser.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/localnetwork_adjustment_results.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/localnetwork_adjustment_results_data.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/localnetworksql.cpp \
$$LIBGAMASRC/lib/gnu_gama/xml/localnetworkxml.cpp \

# expat xml parser

INCLUDEPATH += $$LIBGAMASRC/lib/expat $$LIBGAMASRC/lib/expat/xmltok

HEADERS += \
$$LIBGAMASRC/lib/expat/xmlwf/codepage.h \
$$LIBGAMASRC/lib/expat/xmltok/xmlrole.h \
$$LIBGAMASRC/lib/expat/xmlparse/hashtable.h \
$$LIBGAMASRC/lib/expat/xmlparse/xmlparse.h \
$$LIBGAMASRC/lib/expat/xmltok/xmltok.h \

SOURCES += \
$$LIBGAMASRC/lib/expat/xmlwf/codepage.c \
$$LIBGAMASRC/lib/expat/xmltok/xmlrole.c \
$$LIBGAMASRC/lib/expat/xmlparse/hashtable.c \
$$LIBGAMASRC/lib/expat/xmlparse/xmlparse.c \
$$LIBGAMASRC/lib/expat/xmltok/xmltok.c
