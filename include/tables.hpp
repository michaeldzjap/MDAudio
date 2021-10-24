#ifndef MD_AUDIO_TABLES_HPP
#define MD_AUDIO_TABLES_HPP

#include "constants.hpp"
#include <array>
#include <cmath>
#include <cstdint>

namespace md_audio {

    constexpr std::size_t TABLE_SIZE = 512;
    constexpr double radians_to_increment = TABLE_SIZE / TWO_PI;
    // constexpr double cycles_to_increment = table_size * sample_duration;

    template <typename T>
    constexpr T sine_period(T index) noexcept {
        return std::sin(index / static_cast<T>(radians_to_increment));
    }

    template <typename T>
    constexpr T hann_period(T index) noexcept {
        auto z = std::sin(index * static_cast<T>(PI / static_cast<double>(TABLE_SIZE)));

        return z * z;
    }

    template <typename T, T func(T)>
    constexpr std::array<T, TABLE_SIZE + 1> fill_table() noexcept {
        std::array<T, TABLE_SIZE + 1> table{0};

        for (std::size_t i = 0; i < TABLE_SIZE + 1; i++)
            table[i] = func(static_cast<T>(i));

        return table;
    }

    // As unfortunately std::sin is not supported with constexpr currently we
    // will hard-code our table values

    // constexpr std::array<MdFloat, table_size + 1> sine_table = fill_table<MdFloat, &sine_period>();
    // constexpr std::array<MdFloat, table_size + 1> hann_table = fill_table<MdFloat, &hann_period>();

    constexpr std::array<double, TABLE_SIZE + 1> sine_table = {
        0, 0.012271538285719925, 0.024541228522912288, 0.036807222941358832, 0.049067674327418015, 0.061320736302208578, 0.073564563599667426, 0.085797312344439894, 0.098017140329560604, 0.11022220729388306, 0.1224106751992162, 0.13458070850712617, 0.14673047445536175, 0.15885814333386142, 0.17096188876030122, 0.18303988795514095, 0.19509032201612825, 0.20711137619221853, 0.2191012401568698, 0.23105810828067111, 0.24298017990326387, 0.25486565960451457, 0.26671275747489837, 0.27851968938505306, 0.29028467725446233, 0.30200594931922808, 0.31368174039889146, 0.32531029216226293, 0.33688985339222005, 0.34841868024943456, 0.35989503653498811, 0.37131719395183754, 0.38268343236508978, 0.3939920400610481, 0.40524131400498981, 0.41642956009763715, 0.42755509343028208, 0.43861623853852766, 0.44961132965460654, 0.46053871095824001, 0.47139673682599764, 0.48218377207912272, 0.49289819222978404, 0.50353838372571758, 0.51410274419322166, 0.52458968267846895, 0.53499761988709715, 0.54532498842204646, 0.55557023301960218, 0.56573181078361312, 0.57580819141784534, 0.58579785745643886, 0.59569930449243325, 0.60551104140432555, 0.61523159058062682, 0.62485948814238634, 0.63439328416364549, 0.64383154288979139, 0.65317284295377676, 0.66241577759017178, 0.67155895484701833, 0.68060099779545302, 0.68954054473706683, 0.6983762494089728, 0.70710678118654746, 0.71573082528381859, 0.72424708295146689, 0.73265427167241282, 0.74095112535495899, 0.74913639452345926, 0.75720884650648446, 0.76516726562245885, 0.77301045336273699, 0.78073722857209438, 0.78834642762660623, 0.79583690460888346, 0.80320753148064483, 0.81045719825259477, 0.81758481315158371, 0.82458930278502518, 0.83146961230254524, 0.83822470555483797, 0.84485356524970701, 0.85135519310526508, 0.85772861000027212, 0.8639728561215867, 0.87008699110871135, 0.8760700941954066, 0.88192126434835494, 0.88763962040285393, 0.89322430119551532, 0.89867446569395382, 0.90398929312344334, 0.90916798309052227, 0.91420975570353069, 0.91911385169005777, 0.92387953251128674, 0.92850608047321548, 0.93299279883473885, 0.93733901191257485, 0.94154406518302081, 0.94560732538052128, 0.94952818059303667, 0.95330604035419375, 0.95694033573220882, 0.96043051941556579, 0.96377606579543984, 0.96697647104485207, 0.97003125319454397, 0.97293995220556007, 0.97570213003852846, 0.97831737071962765, 0.98078528040323043, 0.98310548743121629, 0.98527764238894122, 0.98730141815785832, 0.98917650996478101, 0.99090263542778001, 0.99247953459870997, 0.99390697000235606, 0.99518472667219682, 0.996312612182778, 0.99729045667869021, 0.99811811290014918, 0.99879545620517241, 0.99932238458834954, 0.99969881869620425, 0.9999247018391445, 1, 0.9999247018391445, 0.99969881869620425, 0.99932238458834954, 0.99879545620517241, 0.99811811290014918, 0.99729045667869021, 0.996312612182778, 0.99518472667219693, 0.99390697000235606, 0.99247953459870997, 0.99090263542778001, 0.98917650996478101, 0.98730141815785843, 0.98527764238894133, 0.98310548743121629, 0.98078528040323043, 0.97831737071962765, 0.97570213003852857, 0.97293995220556018, 0.97003125319454397, 0.96697647104485207, 0.96377606579543984, 0.9604305194155659, 0.95694033573220894, 0.95330604035419386, 0.94952818059303667, 0.94560732538052139, 0.94154406518302081, 0.93733901191257496, 0.93299279883473896, 0.92850608047321559, 0.92387953251128674, 0.91911385169005777, 0.91420975570353069, 0.90916798309052249, 0.90398929312344345, 0.89867446569395393, 0.89322430119551544, 0.88763962040285393, 0.88192126434835505, 0.8760700941954066, 0.87008699110871146, 0.86397285612158681, 0.85772861000027212, 0.8513551931052652, 0.84485356524970723, 0.83822470555483819, 0.83146961230254546, 0.82458930278502551, 0.81758481315158371, 0.81045719825259477, 0.80320753148064494, 0.79583690460888357, 0.78834642762660634, 0.7807372285720946, 0.7730104533627371, 0.76516726562245907, 0.75720884650648468, 0.74913639452345959, 0.74095112535495899, 0.73265427167241282, 0.72424708295146689, 0.71573082528381871, 0.70710678118654757, 0.69837624940897292, 0.68954054473706705, 0.68060099779545324, 0.67155895484701855, 0.66241577759017201, 0.65317284295377698, 0.64383154288979139, 0.63439328416364549, 0.62485948814238634, 0.61523159058062693, 0.60551104140432566, 0.59569930449243347, 0.58579785745643898, 0.57580819141784545, 0.56573181078361345, 0.55557023301960251, 0.54532498842204669, 0.53499761988709715, 0.52458968267846895, 0.51410274419322177, 0.50353838372571769, 0.49289819222978415, 0.48218377207912289, 0.47139673682599786, 0.46053871095824023, 0.44961132965460687, 0.43861623853852794, 0.42755509343028242, 0.41642956009763715, 0.40524131400498992, 0.39399204006104815, 0.38268343236508989, 0.37131719395183771, 0.35989503653498833, 0.34841868024943479, 0.33688985339222033, 0.32531029216226326, 0.3136817403988918, 0.30200594931922803, 0.29028467725446239, 0.27851968938505317, 0.26671275747489848, 0.25486565960451468, 0.24298017990326407, 0.23105810828067133, 0.21910124015687005, 0.20711137619221884, 0.19509032201612861, 0.18303988795514134, 0.17096188876030122, 0.15885814333386147, 0.1467304744553618, 0.13458070850712628, 0.12241067519921635, 0.11022220729388324, 0.098017140329560826, 0.085797312344440158, 0.073564563599667732, 0.061320736302208932, 0.04906767432741841, 0.036807222941358832, 0.024541228522912326, 0.012271538285720007, 1.2246467991473532e-16, -0.012271538285719762, -0.02454122852291208, -0.036807222941358582, -0.049067674327417724, -0.061320736302208245, -0.073564563599667052, -0.085797312344439478, -0.09801714032956059, -0.110222207293883, -0.1224106751992161, -0.13458070850712606, -0.14673047445536158, -0.15885814333386122, -0.17096188876030097, -0.18303988795514065, -0.19509032201612792, -0.20711137619221817, -0.2191012401568698, -0.23105810828067108, -0.24298017990326382, -0.25486565960451446, -0.26671275747489825, -0.27851968938505289, -0.29028467725446211, -0.30200594931922781, -0.31368174039889118, -0.32531029216226259, -0.33688985339221966, -0.34841868024943456, -0.35989503653498811, -0.37131719395183743, -0.38268343236508967, -0.39399204006104793, -0.40524131400498969, -0.41642956009763693, -0.42755509343028181, -0.43861623853852733, -0.44961132965460626, -0.46053871095823962, -0.47139673682599764, -0.48218377207912266, -0.49289819222978393, -0.50353838372571746, -0.51410274419322155, -0.52458968267846873, -0.53499761988709693, -0.54532498842204613, -0.55557023301960196, -0.5657318107836129, -0.57580819141784489, -0.58579785745643886, -0.59569930449243325, -0.60551104140432543, -0.61523159058062671, -0.62485948814238623, -0.63439328416364527, -0.64383154288979128, -0.65317284295377653, -0.66241577759017145, -0.67155895484701811, -0.68060099779545302, -0.68954054473706683, -0.6983762494089728, -0.70710678118654746, -0.71573082528381848, -0.72424708295146678, -0.73265427167241259, -0.74095112535495888, -0.74913639452345904, -0.75720884650648423, -0.76516726562245896, -0.77301045336273666, -0.78073722857209438, -0.78834642762660589, -0.79583690460888346, -0.8032075314806445, -0.81045719825259466, -0.81758481315158382, -0.82458930278502507, -0.83146961230254524, -0.83822470555483786, -0.84485356524970701, -0.85135519310526486, -0.85772861000027201, -0.86397285612158647, -0.87008699110871135, -0.87607009419540627, -0.88192126434835494, -0.88763962040285405, -0.89322430119551521, -0.89867446569395382, -0.90398929312344312, -0.90916798309052238, -0.91420975570353047, -0.91911385169005766, -0.92387953251128652, -0.92850608047321548, -0.93299279883473862, -0.93733901191257485, -0.94154406518302081, -0.94560732538052117, -0.94952818059303667, -0.95330604035419375, -0.95694033573220882, -0.96043051941556568, -0.96377606579543984, -0.96697647104485196, -0.97003125319454397, -0.97293995220555995, -0.97570213003852846, -0.97831737071962765, -0.98078528040323032, -0.98310548743121629, -0.98527764238894111, -0.98730141815785832, -0.9891765099647809, -0.99090263542778001, -0.99247953459870997, -0.99390697000235606, -0.99518472667219693, -0.996312612182778, -0.99729045667869021, -0.99811811290014918, -0.99879545620517241, -0.99932238458834943, -0.99969881869620425, -0.9999247018391445, -1, -0.9999247018391445, -0.99969881869620425, -0.99932238458834954, -0.99879545620517241, -0.99811811290014918, -0.99729045667869021, -0.996312612182778, -0.99518472667219693, -0.99390697000235606, -0.99247953459871008, -0.99090263542778001, -0.98917650996478113, -0.98730141815785843, -0.98527764238894122, -0.9831054874312164, -0.98078528040323043, -0.97831737071962777, -0.97570213003852857, -0.97293995220556029, -0.97003125319454397, -0.96697647104485229, -0.96377606579543995, -0.96043051941556601, -0.95694033573220894, -0.95330604035419386, -0.94952818059303679, -0.94560732538052128, -0.94154406518302092, -0.93733901191257496, -0.93299279883473907, -0.92850608047321559, -0.92387953251128696, -0.91911385169005788, -0.91420975570353091, -0.90916798309052249, -0.90398929312344334, -0.89867446569395404, -0.89322430119551532, -0.88763962040285416, -0.88192126434835505, -0.87607009419540693, -0.87008699110871146, -0.86397285612158703, -0.85772861000027223, -0.85135519310526553, -0.84485356524970723, -0.83822470555483797, -0.83146961230254546, -0.82458930278502529, -0.81758481315158404, -0.81045719825259488, -0.80320753148064528, -0.79583690460888368, -0.78834642762660667, -0.7807372285720946, -0.77301045336273744, -0.76516726562245918, -0.75720884650648457, -0.74913639452345959, -0.74095112535495911, -0.73265427167241315, -0.724247082951467, -0.71573082528381904, -0.70710678118654768, -0.69837624940897336, -0.68954054473706716, -0.68060099779545358, -0.67155895484701866, -0.66241577759017178, -0.65317284295377709, -0.6438315428897915, -0.63439328416364593, -0.62485948814238645, -0.61523159058062737, -0.60551104140432566, -0.59569930449243391, -0.58579785745643909, -0.57580819141784523, -0.56573181078361356, -0.55557023301960218, -0.5453249884220468, -0.53499761988709726, -0.52458968267846939, -0.51410274419322188, -0.50353838372571813, -0.49289819222978426, -0.48218377207912339, -0.47139673682599792, -0.46053871095823995, -0.44961132965460698, -0.43861623853852766, -0.42755509343028253, -0.41642956009763726, -0.40524131400499042, -0.39399204006104827, -0.38268343236509039, -0.37131719395183782, -0.35989503653498883, -0.3484186802494349, -0.33688985339222, -0.32531029216226337, -0.31368174039889152, -0.30200594931922858, -0.2902846772544625, -0.27851968938505367, -0.26671275747489859, -0.25486565960451524, -0.24298017990326418, -0.23105810828067189, -0.21910124015687016, -0.20711137619221853, -0.19509032201612872, -0.18303988795514101, -0.17096188876030177, -0.15885814333386158, -0.14673047445536239, -0.13458070850712642, -0.1224106751992169, -0.11022220729388336, -0.098017140329561395, -0.085797312344440282, -0.073564563599667412, -0.061320736302209057, -0.049067674327418091, -0.036807222941359394, -0.024541228522912448, -0.012271538285720572, -2.4492935982947064e-16
    };
    constexpr std::array<double, TABLE_SIZE + 1> hann_table = {
        0, 3.7649080427729538e-05, 0.00015059065189788992, 0.00033880770582524954, 0.00060227189741380368, 0.00094094354992539642, 0.001354771660654892, 0.0018436939086109935, 0.0024076366639015569, 0.0030465149988219784, 0.0037602327006450009, 0.0045486822861099865, 0.0054117450176095136, 0.0063492909210708095, 0.0073611788055293779, 0.0084472562843918349, 0.009607359798384776, 0.010841314640186185, 0.012148934980735727, 0.013530023897219924, 0.014984373402728002, 0.016511764477573944, 0.018111967102280063, 0.019784740292217089, 0.021529832133895567, 0.023346979822903083, 0.025235909703481666, 0.027196337309739329, 0.029227967408489607, 0.031330494043712534, 0.033503600582630556, 0.035746959763392212, 0.038060233744356617, 0.040443074154971122, 0.042895122148234675, 0.04541600845473881, 0.048005353438278331, 0.050662767153023078, 0.053387849402242338, 0.056180189798573019, 0.059039367825822475, 0.061964952902296686, 0.064956504445644297, 0.068013571939206624, 0.071135694999863955, 0.07432240344736743, 0.077573217375146442, 0.080887647222581002, 0.084265193848727354, 0.087705348607487341, 0.091207593424208158, 0.094771400873702588, 0.09839623425967757, 0.10208154769555824, 0.10582678618669686, 0.10963138571395278, 0.11349477331863152, 0.11741636718877052, 0.12139557674675773, 0.12543180273827031, 0.12952443732252042, 0.13367286416379356, 0.13787645852426653, 0.14213458735809067, 0.14644660940672624, 0.15081187529551354, 0.15522972763146653, 0.15969950110227343, 0.16422052257649078, 0.16879211120491408, 0.17341357852311159, 0.17808422855510425, 0.18280335791817726, 0.1875702559288068, 0.19238420470968659, 0.19724447929783723, 0.20215034775378327, 0.20710107127178057, 0.21209590429107733, 0.21713409460819341, 0.22221488349019888, 0.22733750578897674, 0.23250119005645137, 0.23770515866076558, 0.24294862790338914, 0.24823080813714124, 0.25355090388510798, 0.25890811396043856, 0.2643016315870011, 0.26973064452088003, 0.27519433517269676, 0.28069188073073609, 0.2862224532848589, 0.2917852199511814, 0.29737934299750513, 0.30300397996947598, 0.30865828381745508, 0.31434140302408126, 0.32005248173250583, 0.32579065987528266, 0.33155507330389, 0.33734485391886854, 0.34315912980055424, 0.3489970253403859, 0.35485766137276881, 0.3607401553074735, 0.36664362126255085, 0.37256717019774271, 0.37850991004836804, 0.38447094585966435, 0.39044937992156503, 0.39644431190389068, 0.40245483899193585, 0.40848005602242948, 0.41451905561984931, 0.42057092833306925, 0.4266347627723191, 0.43270964574643689, 0.43879466240039194, 0.44488889635305845, 0.45099142983521961, 0.45710134382778, 0.46321771820016627, 0.46933963184889566, 0.47546616283629084, 0.48159638852932057, 0.48772938573854396, 0.49386423085714004, 0.49999999999999989, 0.50613576914285996, 0.51227061426145604, 0.51840361147067948, 0.52453383716370894, 0.53066036815110429, 0.53678228179983367, 0.54289865617221977, 0.54900857016478033, 0.55511110364694149, 0.561205337599608, 0.567290354253563, 0.57336523722768074, 0.5794290716669307, 0.58548094438015064, 0.59151994397757035, 0.59754516100806421, 0.60355568809610927, 0.60955062007843475, 0.61552905414033554, 0.62149008995163191, 0.62743282980225734, 0.6333563787374491, 0.6392598446925265, 0.64514233862723103, 0.65100297465961399, 0.6568408701994457, 0.66265514608113141, 0.66844492669611, 0.67420934012471723, 0.67994751826749411, 0.6856585969759188, 0.69134171618254492, 0.69699602003052397, 0.70262065700249476, 0.70821478004881844, 0.71377754671514093, 0.71930811926926363, 0.72480566482730335, 0.73026935547912009, 0.73569836841299896, 0.74109188603956144, 0.74644909611489196, 0.75176919186285873, 0.75705137209661078, 0.76229484133923442, 0.76749880994354858, 0.77266249421102307, 0.77778511650980098, 0.78286590539180656, 0.78790409570892261, 0.79289892872821943, 0.79784965224621673, 0.80275552070216272, 0.80761579529031335, 0.81242974407119317, 0.81719664208182274, 0.82191577144489569, 0.82658642147688821, 0.83120788879508589, 0.83577947742350922, 0.84030049889772662, 0.84477027236853353, 0.84918812470448635, 0.85355339059327373, 0.85786541264190919, 0.86212354147573333, 0.86632713583620635, 0.8704755626774795, 0.87456819726172952, 0.87860442325324239, 0.88258363281122942, 0.88650522668136855, 0.8903686142860473, 0.89417321381330306, 0.89791845230444167, 0.90160376574032242, 0.90522859912629738, 0.90879240657579163, 0.91229465139251253, 0.91573480615127278, 0.91911235277741909, 0.92242678262485345, 0.92567759655263249, 0.92886430500013595, 0.93198642806079346, 0.93504349555435562, 0.93803504709770325, 0.94096063217417747, 0.94381981020142702, 0.9466121505977575, 0.94933723284697691, 0.95199464656172172, 0.9545839915452613, 0.95710487785176535, 0.95955692584502883, 0.96193976625564337, 0.96425304023660774, 0.96649639941736931, 0.96866950595628731, 0.97077203259151035, 0.97280366269026075, 0.97476409029651845, 0.97665302017709688, 0.97847016786610452, 0.98021525970778289, 0.98188803289771986, 0.98348823552242604, 0.98501562659727193, 0.98646997610277998, 0.98785106501926434, 0.98915868535981377, 0.9903926402016151, 0.9915527437156082, 0.99263882119447056, 0.99365070907892905, 0.99458825498239045, 0.99545131771389006, 0.99623976729935493, 0.99695348500117809, 0.99759236333609846, 0.99815630609138895, 0.99864522833934521, 0.99905905645007453, 0.9993977281025862, 0.99966119229417472, 0.99984940934810207, 0.9999623509195722, 1, 0.9999623509195722, 0.99984940934810207, 0.99966119229417472, 0.9993977281025862, 0.99905905645007453, 0.99864522833934521, 0.99815630609138895, 0.99759236333609846, 0.99695348500117809, 0.99623976729935493, 0.99545131771389006, 0.99458825498239045, 0.99365070907892927, 0.99263882119447056, 0.9915527437156082, 0.99039264020161533, 0.98915868535981377, 0.98785106501926434, 0.98646997610277998, 0.98501562659727193, 0.98348823552242604, 0.98188803289771986, 0.98021525970778289, 0.97847016786610452, 0.97665302017709688, 0.97476409029651845, 0.97280366269026075, 0.97077203259151035, 0.96866950595628731, 0.96649639941736931, 0.96425304023660774, 0.96193976625564337, 0.95955692584502883, 0.95710487785176535, 0.9545839915452613, 0.95199464656172172, 0.94933723284697691, 0.94661215059775772, 0.94381981020142702, 0.94096063217417747, 0.93803504709770347, 0.93504349555435562, 0.93198642806079346, 0.92886430500013595, 0.92567759655263249, 0.92242678262485367, 0.91911235277741909, 0.91573480615127278, 0.91229465139251253, 0.90879240657579186, 0.90522859912629738, 0.90160376574032242, 0.89791845230444189, 0.89417321381330328, 0.8903686142860473, 0.88650522668136855, 0.88258363281122942, 0.87860442325324239, 0.87456819726172974, 0.8704755626774795, 0.86632713583620635, 0.86212354147573356, 0.85786541264190941, 0.85355339059327373, 0.84918812470448657, 0.84477027236853353, 0.84030049889772662, 0.83577947742350922, 0.83120788879508589, 0.82658642147688854, 0.82191577144489569, 0.81719664208182297, 0.81242974407119317, 0.80761579529031358, 0.80275552070216283, 0.79784965224621651, 0.79289892872821965, 0.78790409570892261, 0.78286590539180678, 0.7777851165098012, 0.77266249421102329, 0.76749880994354858, 0.76229484133923464, 0.75705137209661089, 0.75176919186285895, 0.74644909611489219, 0.74109188603956122, 0.73569836841299896, 0.73026935547912009, 0.72480566482730335, 0.71930811926926375, 0.71377754671514126, 0.70821478004881866, 0.70262065700249521, 0.69699602003052419, 0.69134171618254525, 0.6856585969759188, 0.67994751826749389, 0.67420934012471745, 0.66844492669611, 0.66265514608113174, 0.6568408701994457, 0.65100297465961432, 0.64514233862723125, 0.63925984469252684, 0.63335637873744921, 0.62743282980225712, 0.62149008995163202, 0.61552905414033543, 0.60955062007843508, 0.60355568809610927, 0.59754516100806432, 0.59151994397757035, 0.58548094438015086, 0.57942907166693081, 0.57336523722768107, 0.56729035425356311, 0.561205337599608, 0.55511110364694172, 0.54900857016478011, 0.54289865617222011, 0.53678228179983367, 0.5306603681511044, 0.52453383716370894, 0.51840361147067959, 0.51227061426145626, 0.50613576914286029, 0.50000000000000011, 0.49386423085713987, 0.48772938573854396, 0.48159638852932057, 0.47546616283629117, 0.46933963184889566, 0.46321771820016655, 0.45710134382778, 0.45099142983521989, 0.44488889635305856, 0.43879466240039222, 0.432709645746437, 0.42663476277231899, 0.42057092833306942, 0.41451905561984931, 0.40848005602242965, 0.40245483899193585, 0.39644431190389096, 0.39044937992156503, 0.38447094585966474, 0.37850991004836815, 0.37256717019774299, 0.36664362126255096, 0.36074015530747339, 0.35485766137276897, 0.3489970253403859, 0.34315912980055441, 0.33734485391886854, 0.33155507330389017, 0.32579065987528266, 0.32005248173250622, 0.31434140302408137, 0.30865828381745508, 0.30300397996947609, 0.29737934299750501, 0.29178521995118151, 0.2862224532848589, 0.28069188073073637, 0.27519433517269676, 0.26973064452088014, 0.26430163158700121, 0.25890811396043889, 0.25355090388510809, 0.24823080813714113, 0.24294862790338925, 0.23770515866076547, 0.23250119005645153, 0.22733750578897674, 0.22221488349019908, 0.21713409460819341, 0.21209590429107752, 0.20710107127178062, 0.20215034775378357, 0.19724447929783731, 0.19238420470968651, 0.18757025592880691, 0.1828033579181772, 0.17808422855510442, 0.17341357852311159, 0.16879211120491427, 0.16422052257649083, 0.15969950110227366, 0.15522972763146659, 0.15081187529551379, 0.14644660940672632, 0.14213458735809059, 0.13787645852426667, 0.13367286416379354, 0.12952443732252059, 0.12543180273827034, 0.12139557674675788, 0.11741636718877056, 0.11349477331863171, 0.10963138571395281, 0.10582678618669708, 0.10208154769555831, 0.098396234259677501, 0.094771400873702685, 0.09120759342420813, 0.087705348607487479, 0.084265193848727396, 0.080887647222581127, 0.077573217375146497, 0.074322403447367583, 0.07113569499986401, 0.068013571939206804, 0.064956504445644353, 0.061964952902296658, 0.059039367825822572, 0.056180189798573012, 0.053387849402242435, 0.050662767153023078, 0.048005353438278442, 0.045416008454738831, 0.042895122148234793, 0.04044307415497117, 0.038060233744356756, 0.035746959763392275, 0.033503600582630536, 0.031330494043712603, 0.029227967408489607, 0.027196337309739412, 0.025235909703481677, 0.023346979822903159, 0.021529832133895584, 0.019784740292217183, 0.01811196710228009, 0.016511764477573923, 0.014984373402728041, 0.013530023897219913, 0.012148934980735767, 0.010841314640186181, 0.0096073597983848194, 0.0084472562843918401, 0.007361178805529423, 0.0063492909210708208, 0.0054117450176095587, 0.0045486822861100029, 0.00376023270064499, 0.0030465149988219962, 0.0024076366639015521, 0.0018436939086110106, 0.001354771660654892, 0.00094094354992541116, 0.00060227189741380552, 0.00033880770582525989, 0.00015059065189789193, 3.7649080427733509e-05, 1.4997597826618576e-32
    };

}

#endif /* MD_AUDIO_TABLES_HPP */
