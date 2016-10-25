#include <inttypes.h>

#define VOL_TYPE_BASE (uint8_t) 0
#define VOL_TYPE_ANNX (uint8_t) 1
#define VOL_TYPE_OTHER (uint8_t) 2


#define VOL_BLOCK_SIZE 128

typedef unsigned char block_t[VOL_BLOCK_SIZE];


typedef struct cyl_sec_s {
	uint16_t cylinder, sector;
} __attribute__((packed)) cyl_sec_s;

typedef struct vol_s {
	cyl_sec_s first;
	uint32_t nbSector;
	uint8_t type;
} __attribute__((packed)) vol_s;

#define NB_MAX_VOL 8
#define MBR_MAGIC 0xB00B

typedef struct mbr_s {
	uint8_t nbVol;
	vol_s volumes[NB_MAX_VOL];
	
	uint16_t magic;
} __attribute__((packed)) mbr_s;







/**
 * Initialisation du disque et du MBR
 */
void vol_drive_start();






void vol_read_bloc(uint8_t vol, uint32_t nbloc, block_t* buffer);
void vol_write_bloc(uint8_t vol, uint32_t nbloc, block_t* buffer);
void vol_format_vol(uint8_t vol);





/**
 * Affiche dans stdout les infos du disque dur et des volumes actuels
 */
void vol_print_infos();

/**
 * retourne le nombre de volume actuellement dans le disque
 */
uint8_t vol_get_nb_volumes();

/**
 * retourne le nombre de bloc dans le volume à l'index indiqué en paramètre.
 */
uint32_t vol_get_nb_blocks(uint8_t vol);

/**
 * Ajoute le volume passé en paramètre. Vérifie la validité et si le
 * nombre de volume maximum n'est pas encore atteint avant d'effectuer
 * l'opération d'ajout.
 * retourne 1 si réussi (si le volume fourni est valide), 0 sinon
 */
int vol_add_volume(vol_s volume);

/**
 * Supprime le volume à l'index indiqué en paramètre.
 * Tous les volumes se trouvant aux index suivants sont décalés vers
 * l'index qui leur précède.
 * retourne 1 si réussi, 0 sinon
 */
int vol_remove_volume(uint8_t vol);
