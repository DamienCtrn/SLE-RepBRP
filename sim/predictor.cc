#include "predictor.h"

/////////////// STORAGE BUDGET JUSTIFICATION ////////////////

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

// Constructeur du prédicteur
PREDICTOR::PREDICTOR(char *prog, int argc, char *argv[])
{
   // La trace est tjs présente, et les arguments sont ceux que l'on désire
   if (argc != 2) {
      fprintf(stderr, "usage: %s <trace> history_length\n", prog);
      exit(-1);
   }

   history_length = strtoul(argv[0], NULL, 0);

   // nombre d'entrées dans la table
   uint32_t nb_enties = (1 << history_length);
   // Construction du masque
   history_mask = 1;
   for (size_t i = 0; i < history_length - 1; i++) {
	   history_mask <<= 1;
	   history_mask ++;
   }
   // Allocation de la table
   table = new uint32_t[nb_enties]();
   history = 0;
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

bool PREDICTOR::GetPrediction()
{
	return table[history & history_mask];
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

void PREDICTOR::UpdatePredictor(bool resolveDir)
{
	table[history & history_mask] = resolveDir;
	history <<= 1;
	history = (resolveDir == TAKEN) ? history + 1 : history;
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

void PREDICTOR::TrackOtherInst(UINT64 PC, OpType opType, bool branchDir, UINT64 branchTarget)
{
   // This function is called for instructions which are not
   // conditional branches, just in case someone decides to design
   // a predictor that uses information from such instructions.
   // We expect most contestants to leave this function untouched.
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////


/***********************************************************/
