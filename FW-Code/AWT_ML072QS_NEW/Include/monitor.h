/* monitor.h */


void Mon_tx(BYTE ch);

void MonHelp(void);
BYTE MonGetCommand(void);

void Monitor(void);

void Prompt(void);

BYTE GetMonAddress(void);
#ifdef Monitor_debug
void SetMonAddress(BYTE addr);
#endif
void MonReadI2C(void);
void MonWriteI2C(void);

