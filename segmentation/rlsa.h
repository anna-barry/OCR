#ifndef RLSA_H
#define RLSA_H

Matrix horizonRLSA (Matrix img, int seuil);

Matrix verticRLSA (Matrix img, int seuil);

Matrix rlsa(Matrix img, int verticSeuil, int horizonSeuil);

#endif
