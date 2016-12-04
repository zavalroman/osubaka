
#include "samples.h"

Samples::Samples( const char* defaultPath, const char* skinPath )
{
	int skinHsSetMask = 0;//fs.getSkinHsSet ( skinPath ); //see "hsbits"
	//int defaultHsSet = 2097151; // pow ( 2, 21 ) - 1;	// twenty one bits is true -- full hs set ( normal, soft, drum x normal, whistle, finish, clap, slide, tick, whistle )
	//defaultHsSet = defaultHsSet ^ skinHsSetMask; // need to load hs from default skin
		
	for ( int i = 0; i < 21; i++ )
		if ( skinHsSetMask & 1 << i ) { // не факт, что условие выполняется корректно. вероятно, сначала выполняется &, потом сдвиг, поэтому результат ВСЕГДА _ложь_
			loadHitSound( i, skinPath, 0 );
		} else {
			loadHitSound( i, defaultPath, 0 );
		}
		
	data_= OpenAlContext::open( "/home/roman/develop/osu/Skins/Default/normal-hitnormal.wav" );
	
	sound_ = new Sound( data_, false );

}

void Samples::loadHitSound( int bit, const char* place, int hsSet )
{
	char* file;
	const char* section;
	const char* type;
	char* set = new char[4];
	int length = strlen( place );
	bool repeat = false;
	
	if ( bit == 4 || bit == 11 || bit == 18 ) repeat = true; // for sliderslide
	
	for ( int i = 2; i >= 0; i-- )
		if ( bit > 7 * i - 1 ) {
			section = sections[i];
			length += strlen( section );
			type = types[ bit - 7 * i ];
			length += strlen( type );
			break;
		}
	
	int n = sprintf( set, "%d", hsSet );
	length += hsSet > 0 ? n : 0;
	length += 4; // strlen ( ".wav" );
	
	file = new char[ length + 1 ];
	
	strcpy( file, place );
	strcat( file, section );
	strcat( file, type );
	
	if ( hsSet ) strcat( file, set );
		
	strcat( file, ".wav" );
	//std::cout << file << std::endl;
	baseHs[ bit ].data = OpenAlContext::open( file );
	//std::cout << bit << "    <>   " << repeat << std::endl;
	baseHs[ bit ].sound = new Sound( baseHs[ bit ].data, false );
	
	delete set;
	delete file;
}

void Samples::playHitSound( int clickResult, int sampleType ) // sampleType == 0 -- normal, 1 -- soft, 2 -- drum
{
	//int type = sampleType * 7; 								!!!
	
	if ( baseHs[ 0 + sampleType * 7 ].sound->isPlaying() )
		baseHs[ 0 + sampleType * 7 ].sound->stop();
	baseHs[ 0 + sampleType * 7 ].sound->play();

	if ( clickResult & 2 ) {
		if ( baseHs[ 1 + sampleType * 7 ].sound->isPlaying() )
			baseHs[ 1 + sampleType * 7 ].sound->stop();
		baseHs[ 1 + sampleType * 7 ].sound->play();
	}
	if ( clickResult & 4 ) {
		if ( baseHs[ 2 + sampleType * 7 ].sound->isPlaying() )
			baseHs[ 2 + sampleType * 7 ].sound->stop();
		baseHs[ 2 + sampleType * 7 ].sound->play();
	}
	if ( clickResult & 8 ) {
		if ( baseHs[ 3 + sampleType * 7 ].sound->isPlaying() )
			baseHs[ 3 + sampleType * 7 ].sound->stop();
		baseHs[ 3 + sampleType * 7 ].sound->play();
	}

}

void Samples::playHS( int j )
{
	sound_->play ();
}
