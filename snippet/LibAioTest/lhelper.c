#include <stdio.h>
#include <stdlib.h>


#define ERR_EXIT(func)  \
    do                  \
    {                   \
        perror("func"); \
        exit(1);        \
    } while (0)


static const char *s =
    "浔阳江头夜送客，枫叶荻花秋瑟瑟。\n"
    "主人下马客在船，举酒欲饮无管弦。\n"
    "醉不成欢惨将别，别时茫茫江浸月。\n"
    "忽闻水上琵琶声，主人忘归客不发。\n"
    "寻声暗问弹者谁？琵琶声停欲语迟。\n"
    "移船相近邀相见，添酒回灯重开宴。\n"
    "千呼万唤始出来，犹抱琵琶半遮面。\n"
    "转轴拨弦三两声，未成曲调先有情。\n"
    "弦弦掩抑声声思，似诉平生不得志。\n"
    "低眉信手续续弹，说尽心中无限事。\n"
    "轻拢慢捻抹复挑，初为《霓裳》后《六幺》。\n"
    "大弦嘈嘈如急雨，小弦切切如私语。\n"
    "嘈嘈切切错杂弹，大珠小珠落玉盘。\n"
    "间关莺语花底滑，幽咽泉流冰下难。\n"
    "水泉冷涩弦凝绝，凝绝不通声暂歇。\n"
    "别有幽愁暗恨生，此时无声胜有声。\n"
    "银瓶乍破水浆迸，铁骑突出刀枪鸣。\n"
    "曲终收拨当心画，四弦一声如裂帛。\n"
    "东船西舫悄无言，唯见江心秋月白。\n"
    "沉吟放拨插弦中，整顿衣裳起敛容。\n"
    "自言本是京城女，家在虾蟆陵下住。\n"
    "十三学得琵琶成，名属教坊第一部。\n"
    "曲罢曾教善才服，妆成每被秋娘妒。\n"
    "五陵年少争缠头，一曲红绡不知数。\n"
    "钿头银篦击节碎，血色罗裙翻酒污。\n"
    "今年欢笑复明年，秋月春风等闲度。\n"
    "弟走从军阿姨死，暮去朝来颜色故。\n"
    "门前冷落鞍马稀，老大嫁作商人妇。\n"
    "商人重利轻别离，前月浮梁买茶去。\n"
    "去来江口守空船，绕船月明江水寒。\n"
    "夜深忽梦少年事，梦啼妆泪红阑干。\n"
    "我闻琵琶已叹息，又闻此语重唧唧。\n"
    "同是天涯沦落人，相逢何必曾相识！\n"
    "我从去年辞帝京，谪居卧病浔阳城。\n"
    "浔阳地僻无音乐，终岁不闻丝竹声。\n"
    "住近湓江地低湿，黄芦苦竹绕宅生。\n"
    "其间旦暮闻何物？杜鹃啼血猿哀鸣。\n"
    "春江花朝秋月夜，往往取酒还独倾。\n"
    "岂无山歌与村笛？呕哑嘲哳难为听。\n"
    "今夜闻君琵琶语，如听仙乐耳暂明。\n"
    "莫辞更坐弹一曲，为君翻作《琵琶行》。\n"
    "感我此言良久立，却坐促弦弦转急。\n"
    "凄凄不似向前声，满座重闻皆掩泣。\n"
    "座中泣下谁最多？江州司马青衫湿。\n";


void prepareFile(const char *path)
{
    FILE *pFile = fopen(path, "w");
    if (!pFile) ERR_EXIT("fopen");

    fputs(s, pFile);

    fclose(pFile);
}

void removeFile(const char *path)
{
    remove(path);
}
