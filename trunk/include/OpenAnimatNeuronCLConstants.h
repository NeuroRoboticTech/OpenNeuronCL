#ifndef __NEURAL_CONSTANTS_H__
#define __NEURAL_CONSTANTS_H__

#define Nl_Err_lSynapseToAddNull -3013
#define Nl_Err_strSynapseToAddNull "Synapse to be added to the Neuron is null."

#define Nl_Err_lInvalidSynapseIndex -3014
#define Nl_Err_strInvalidSynapseIndex "An invalid Synapse index value was specified."

#define Nl_Err_lInvalidSizeSpec -3006
#define Nl_Err_strInvalidSizeSpec "Invalid Size specification."

#define Nl_Err_lNeuronToSetNull -3007
#define Nl_Err_strNeuronToSetNull "The neuron to set was null."

#define Nl_Err_lSimulationNotDefined -3024
#define Nl_Err_strSimulationNotDefined "Simulation has not been defined."

#define Nl_Err_lInvalidExternalStimulusType -3027
#define Nl_Err_strInvalidExternalStimulusType "Invalid external stimulus type."

#define Nl_Err_lInvalidNeuronType -3000
#define Nl_Err_strInvalidNeuronType "Invalid neuron type."

#define Nl_Err_lInvalidSynapseType -3001
#define Nl_Err_strInvalidSynapseType "Invalid synapse type."

#define Nl_Err_lInvalidNeuronDataType -3009
#define Nl_Err_strInvalidNeuronDataType "Invalid neuron data type was specified."

#define Nl_Err_lInvalidSynapseDataType -3010
#define Nl_Err_strInvalidSynapseDataType "Invalid synapse data type was specified."

#define Nl_Err_lIDBlank -3020
#define Nl_Err_strIDBlank "ID is blank."

#define Nl_Err_lNeuronNotFound -3030
#define Nl_Err_strNeuronNotFound "The specified neuron was not found."

#define Nl_Err_lSynapseNotFound -3031
#define Nl_Err_strSynapseNotFound "The specified synapse was not found."

#define Nl_Err_lNeuronNotSpikingType -3032
#define Nl_Err_strNeuronNotSpikingType "The neuron passed to the Spiking core was not a spiking type."

#define Nl_Err_lSynapseNotSpikingType -3033
#define Nl_Err_strSynapseNotSpikingType "The synapse passed to the Spiking synapse core was not a spiking type."

#define Nl_Err_lSynapseTypeNotSpikingType -3034
#define Nl_Err_strSynapseTypeNotSpikingType "The synapse type was not a spiking type."

#define Nl_Err_lNeuronTypeNotSpikingType -3034
#define Nl_Err_strNeuronTypeNotSpikingType "The neuron type was not a spiking type."

#define Nl_Err_lNeuronNotCorrectType -30335
#define Nl_Err_strNeuronNotCorrectType "The neuron was not the correct type."

#define Nl_Err_lInvalidRunMode -30336
#define Nl_Err_strInvalidRunMode "Invalid run mode."

#define Nl_Err_lFixedValLengthDiff -30337
#define Nl_Err_strFixedValLengthDiff "The bit definitions of two fixed values that are being manipulated are not the same."

#define Nl_Err_lNeuronTypeNotFound -30338
#define Nl_Err_strNeuronTypeNotFound "The specified neuron type was not found."

#define Nl_Err_lSynapseTypeNotFound -30339
#define Nl_Err_strSynapseTypeNotFound "The specified synapse type was not found."

#define Eb_Err_lInvalidHandle -1000
#define Eb_Err_strInvalidHandle "Invalid connection handle."

#define Eb_Err_lMPU_Proc_Addr -1001
#define Eb_Err_strMPU_Proc_Addr "Unable to get the mpusbapi processes addresses."

#define Eb_Err_lLoadLibrary -1002
#define Eb_Err_strLoadLibrary "Error loading the mpusbapi library."

#define Eb_Err_lOpening_Device -1003
#define Eb_Err_strOpening_Device "Error opening the specified instance of the eBrain board."

#define Eb_Err_lDev_Instance_Invalid -1004
#define Eb_Err_strDev_Instance_Invalid "Specified device instance is invalid."

#define Eb_Err_lNo_Devices_Found -1005
#define Eb_Err_strNo_Devices_Found "No eBrain boards were found to be connected to this computer."

#define Eb_Err_lStarting_Programming -1006
#define Eb_Err_strStarting_Programming "The application was unable to send the program start command to the ebrain board."

#define Eb_Err_lEnding_Programming -1007
#define Eb_Err_strEnding_Programming "The application was unable to send the program end command to the ebrain board."

#define Eb_Err_lStarting_Read -1008
#define Eb_Err_strStarting_Read "The application was unable to send the read start command to the ebrain board."

#define Eb_Err_lEnding_Reading -1009
#define Eb_Err_strEnding_Reading "The application was unable to send the read end command to the ebrain board."

#define Eb_Err_lReading_Data -1010
#define Eb_Err_strReading_Data "An error occurred while reading a data packet from the eBrain."

#define Eb_Err_lInvalid_Comm_Pipes -1011
#define Eb_Err_strInvalid_Comm_Pipes "Atempted to communicate with invalid pipe addresses. Please open the connection!"

#define Eb_Err_lOpeningBitFile -1012
#define Eb_Err_strOpeningBitFile "Unable to open the specified bit file."

#define Eb_Err_lBitFileEmpty -1013
#define Eb_Err_strBitFileEmpty "Specified bit file is empty!"

#define Eb_Err_lInvalidHexValue -1014
#define Eb_Err_strInvalidHexValue "Invalid Hex value specified."

#define Eb_Err_lSending_Read_Data -1016
#define Eb_Err_strSending_Read_Data "Error sending the read data command to the e-Brain."

#define Eb_Err_lTransmit_Array_Too_Small -1017
#define Eb_Err_strTransmit_Array_Too_Small "The transmit array must be a multiple of 64 bytes in size."

#define Eb_Err_lWriting_Data -1018
#define Eb_Err_strWriting_Data "The amount of data transmitted did not match the requested amount."

#define Eb_Err_lSending_Program_Data -1018
#define Eb_Err_strSending_Program_Data "Error sending the PROGRAM_DATA Command."

#define Eb_Err_lChecksumInvalid -1019
#define Eb_Err_strChecksumInvalid "Invalid checksum."

#define Eb_Err_lIncorrectProgEndResponse -1020
#define Eb_Err_strIncorrectProgEndResponse "Invalid PROGRAM_END response from microcontroller."

#define Eb_Err_lSendingProgEnd -1021
#define Eb_Err_strSendingProgEnd "Error sending the PROGRAM_END Command."

#define Eb_Err_lIncorrectProgStartResponse -1022
#define Eb_Err_strIncorrectProgStartResponse "Invalid PROGRAM_START response from microcontroller."

#define Eb_Err_lProgramingFPGA -1023
#define Eb_Err_strProgramingFPGA "An error occured while programing the FPGA."

#define Eb_Err_lMapNotFound -1024
#define Eb_Err_strMapNotFound "Map item not found."

//Set this define to switch to 32 bit fixed point numbers. Comment it out to use the 
//bit widths for the FPGA
#define BIT_SIZE_32

#pragma region BitSizeDefs

#ifdef BIT_SIZE_32

	#define FIXED_M_BITS 7
	#define FIXED_N_BITS 24

	#define VOLT_M_BITS 7
	#define VOLT_N_BITS 24

	#define COND_M_BITS 8
	#define COND_N_BITS 23

	#define DECAY_M_BITS 0
	#define DECAY_N_BITS 31

	#define REFCOUNT_M_BITS 0
	#define REFCOUNT_N_BITS 9

	#define WADJ_M 5
	#define WADJ_N 26

	#define NEURON_TYPE_INDEX_M 6
	#define NEURON_TYPE_INDEX_N 0

	#define SYNAPSE_TYPE_INDEX_M 6
	#define SYNAPSE_TYPE_INDEX_N 0

	#define NEURON_TYPE_SIZE 64
	#define SYNAPSE_TYPE_SIZE 64

#else
	//#define FIXED_M_BITS 6
	//#define FIXED_N_BITS 9

	//#define VOLT_M_BITS 6
	//#define VOLT_N_BITS 9

	//#define COND_M_BITS 6
	//#define COND_N_BITS 9

	//#define DECAY_M_BITS 0
	//#define DECAY_N_BITS 15

	//#define REFCOUNT_M_BITS 0
	//#define REFCOUNT_N_BITS 9

	#define FIXED_M_BITS 6
	#define FIXED_N_BITS 11

	#define VOLT_M_BITS 6
	#define VOLT_N_BITS 11

	#define COND_M_BITS 8
	#define COND_N_BITS 9

	#define DECAY_M_BITS 0
	#define DECAY_N_BITS 17

	#define REFCOUNT_M_BITS 0
	#define REFCOUNT_N_BITS 9

	#define NEURON_TYPE_INDEX_M 6
	#define NEURON_TYPE_INDEX_N 0

	#define SYNAPSE_TYPE_INDEX_M 6
	#define SYNAPSE_TYPE_INDEX_N 0

	#define NEURON_TYPE_SIZE 64
	#define SYNAPSE_TYPE_SIZE 64

#endif

#pragma endregion


#define MODULE_NAME "eBrainSim"

#define ACTION_POTENTIAL_VOLTAGE 0

#define WEIGHT_MANAGER_RANGE 15

//Neuron Types
#define NO_NEURON 0
#define SPIKING_NEURON_FP 1
#define SPIKING_NEURON_RP 2

//Synapse Types
#define NO_SYNAPSE 0
#define SPIKING_SYNAPSE_FP 1
#define SPIKING_SYNAPSE_RP 2

//Data Column Types
#define NEURON_DATA_COLUMN 0
#define SYNAPSE_DATA_COLUMN 1

//External Stimulus Types
#define CURRENT_STIMULUS 0

//Data Types
#define EXTERNAL_CURRENT_DATA 1
#define SYNAPTIC_CURRENT_DATA 2
#define MEMBRANE_VOLTAGE_DATA 3

//NeuralModule Types
#define FPGA_NEURAL_MODULE 0

//Class Types
#define DATA_COLUMN_CLASS 0
#define EXTERNAL_STIMULUS_CLASS 1
#define NEURON_CLASS 2
#define SYNAPSE_CLASS 3
#define NEURAL_MODULE_CLASS 4

//Run Mode Defs
#define FIXED_POINT_RUN_MODE 1
#define FLOATING_POINT_RUN_MODE 2

#define PI 3.14159
#define PI_2 6.28319

#define RAM_64K_SIZE 1024*64
#define RAM_1K_SIZE 1024

#define READ_VERSION        0
#define PROGRAM_START		2
#define PROGRAM_DATA		3
#define PROGRAM_END			4
#define READ_START			5
#define READ_DATA			6
#define READ_END			7
#define ERROR_MSG			8
#define PROGRAM_FPGA		9
#define PROGRAM_DATA2		10
#define CONFIGURE_START		11
#define CONFIGURE_DATA		12
#define CONFIGURE_END		13

#define FLASH_STORAGE				0
#define RAM_STORAGE					1
#define CONFIG_FPGA_FROM_FLASH		2
#define CONFIG_FPGA_FROM_RAM		3

#define MAX_FRAME_BUFFER_READS 18
#define PACKET_LEN    64
#define DATA_PACKET_LEN 62
#define UC_BUFFER_LEN 768
#define FRAME_LEN (MAX_FRAME_BUFFER_READS*UC_BUFFER_LEN)
#define PACKETS_PER_FRAME (FRAME_LEN/PACKET_LEN)

//Class Type constants.
#define SPIKING_NEURON_CLASS 0
#define FAST_SPIKING_NEURON_CLASS 1
#define SPIKING_SYNAPSE_CLASS 2
#define FAST_SPIKING_SYNAPSE_CLASS 3

#define SPIKING_NEURON_TYPE_CLASS 4
#define FAST_SPIKING_NEURON_TYPE_CLASS 5
#define SPIKING_SYNAPSE_TYPE_CLASS 6
#define FAST_SPIKING_SYNAPSE_TYPE_CLASS 7

#endif // __NEURAL_CONSTANTS_H__
