
#ifndef HERO_H
#define HERO_H

#include "character.h"
#include "equipment.h"
#include "bag.h"
#include "skill.h"

class Map;

class Hero : public Character
{
    Q_OBJECT

public:
    enum HeroClasses{
        eSwordman,
        eArcher,
        eWizard,
        eNbHeroClasses
    };
    enum SkillStepEnum{
        Life,
        Mana,
        Stamina,
        Strength,
        NbSkillSteps
    };

    struct HeroCaracteristics{
        QString name;
        int life;
        int mana;
        int stamina;
        int coin;
        int skillPoints;
        Weapon * weapon;
        SkillStep steps;
    };

    struct HeroMovementHandler{
        qreal angle;
        QPointF destPos;
        QTimer * t_move;
        QPointF lastPos;
    };

    struct Experience{
        int points;
        int level;
        int pointsToLevelUp;
    };

public:
    Hero();
    ~Hero();
signals:
    void sig_equipmentChanged();
    void sig_bagEvent();
    void sig_bagFull();
    void sig_coinChanged();
    void sig_experienceChanged();
    void sig_skillPointsChanged();
    void sig_skillUnlocked();
    void sig_heroMoved();
    void sig_showHeroData();
    void sig_ThrowItem(Item*);
    void sig_dodge();
    void sig_playSound(int);
private slots:
    void move();
public:
    QPointF getLocation();
    Bag * getBag();
    Gear * getGear();
    int getCoin();
    Experience getExperience();
    int getSkillPoints();
    Skill* getPassiveSkill(int index);
    Skill* getSpellSkill(int index);
    PassiveSkill ** getSkillList();
    SpellSkill ** getSpellList();
    virtual int getHeroClass()=0;

    void setLocation(QPointF);
    void setGear(Gear*);
    void setPayload(int);
    void setCoin(int);
    void setIsInVillage(bool);
    void setSkillPoints(int);
public:
    void useConsumable(Consumable*);
    void useScroll(Scroll*);
    bool takeItem(Item*);
    void throwItem(Item*);
    qreal calculateDamage();
    int getAttackSpeed();
    void takeDamage(int);
    void addCoin(int);
    bool removeCoin(int);
    bool addExperience(int);
    bool learnSkill(Skill*);
    bool learnPassiveSkill(int);
    void levelUpHero();
    void startMovingTo(int,int);
    void stopMoving();
    void interactWithPNG(bool);
    bool isInteractingWithPNG();
    bool isInVillage();
    bool isDead();
    void freeze(bool);
    bool isFreeze();
public:
    virtual void serialize(QDataStream& stream)const=0;
    virtual void deserialize(QDataStream& stream)=0;
    friend QDataStream& operator<<(QDataStream& stream, const Hero& object)
    {
        object.serialize(stream);
        return stream;
    }
    friend QDataStream& operator>>(QDataStream& stream, Hero& object)
    {
        object.deserialize(stream);
        return stream;
    }
public:
    static Hero * getInstance(Hero::HeroClasses);
public:
    HeroMovementHandler mMoveHandler;
protected:
    Bag * mBag;
    Gear * mGear;
    int mCoin;
    Experience mExperience;
    int mImageSelected;
    bool mInteractionPNG;
    bool mIsInVillage;
    bool mFreeze;
    int mSkillPoints;
    quint8 mClass;
    HeroCaracteristics mHeroList[Hero::eNbHeroClasses] = {
        { "Maphistos", 200, 100, 200, 20, 5, new Weapon("baton", QPixmap(":/equipment/sword_stick.png"), 5, 8, 5, 1), {3, 4, 5, 3} },
        { "Sophia", 140, 120, 300, 25, 5, new Weapon("bow", QPixmap(":/equipment/sword_stick.png"), 12, 8, 5, 1), {2, 4, 7, 2} },
        { "Archangelie", 150, 250, 150, 30, 10, new Weapon("baton", QPixmap(":/equipment/sword_stick.png"), 5, 8, 5, 1), {2, 7, 2, 2} }
    };
    PassiveSkill* mSkillList[PassiveSkill::NbSkills] = {
        new PassiveSkill( PassiveSkill::ForceOfNature, ABLE(eSwordman), "Force de la nature", 2, "Accorde un pourcentage de chance de frapper plus fort en combat", false, QPixmap(":/icons/skill/skill00.png"), QPixmap(":/icons/skill/skill01.png")) ,
        new PassiveSkill( PassiveSkill::InnateRobustness, ABLE(eSwordman), "Robustesse inn??e", 2, "Permet parfois d???encaisser moins de d??g??t en combat", false, QPixmap(":/icons/skill/skill10.png"), QPixmap(":/icons/skill/skill11.png")),
        new PassiveSkill( PassiveSkill::GodBenediction, ABLE(eSwordman)|ABLE(eArcher), "B??n??diction de Dieux", 10, "Accorde parfois un l??ger soin pendant les combats", false, QPixmap(":/icons/skill/skill20.png"), QPixmap(":/icons/skill/skill21.png")),
        new PassiveSkill( PassiveSkill::OutstandingMerchant, ABLE(eSwordman)|ABLE(eArcher)|ABLE(eWizard), "Marchand hors pair", 8, "Permet de revendre vos objets 1.5x plus ch??re chez le marchant", false, QPixmap(":/icons/skill/skill30.png"), QPixmap(":/icons/skill/skill31.png")),
        new PassiveSkill( PassiveSkill::LuckFactor, ABLE(eSwordman)|ABLE(eArcher)|ABLE(eWizard), "Facteur chance", 2, "Vous avez tendance ?? obtenir plus d???objets dans les coffres", false, QPixmap(":/icons/skill/skill40.png"), QPixmap(":/icons/skill/skill41.png")),
        new PassiveSkill( PassiveSkill::Gemologist, ABLE(eSwordman)|ABLE(eArcher)|ABLE(eWizard), "Gemmologue", 2, "Vous avez des chances de r??colter des pierres pr??cieuses sur n???importe quel type de minerai", false, QPixmap(":/icons/skill/skill50.png"), QPixmap(":/icons/skill/skill51.png")),
        new PassiveSkill( PassiveSkill::ConfirmedFisherman, ABLE(eSwordman)|ABLE(eArcher)|ABLE(eWizard), "P??cheur confirm??", 2, "Vous p??cherez plus de poissons", false, QPixmap(":/icons/skill/skill60.png"), QPixmap(":/icons/skill/skill61.png")),
        new PassiveSkill( PassiveSkill::SkinningExpert, ABLE(eSwordman)|ABLE(eArcher)|ABLE(eWizard), "Expert en d??pe??age", 2, "Vous obtiendrez plus de composants de monstre", false, QPixmap(":/icons/skill/skill70.png"), QPixmap(":/icons/skill/skill71.png")),
        new PassiveSkill( PassiveSkill::ManaCollector, ABLE(eWizard), "Collecteur de mana", 15, "Vous puisez en continue le mana ambiant, ce qui vous restore votre mana sur la dur??e", false, QPixmap(":/icons/skill/skill80.png"), QPixmap(":/icons/skill/skill81.png")),
        new PassiveSkill( PassiveSkill::LifeCollector, ABLE(eWizard), "Collecteur de vie", 15, "Vous puisez l?????nergie vitale ambiante, ce qui vous restore de la vie sur la dur??e", false, QPixmap(":/icons/skill/skill90.png"), QPixmap(":/icons/skill/skill91.png")),
        new PassiveSkill( PassiveSkill::MageApprentice, ABLE(eArcher)|ABLE(eWizard), "Apprenti mage", 5, "Permet d???apprendre des sorts basiques", false, QPixmap(":/icons/skill/skill100.png"), QPixmap(":/icons/skill/skill101.png")),
        new PassiveSkill( PassiveSkill::Archmage, ABLE(eWizard), "Archimage", 20, "Permet d???apprendre des sorts de haut niveau", false, QPixmap(":/icons/skill/skill110.png"), QPixmap(":/icons/skill/skill111.png") )
    };

    SpellSkill* mSpellList[SpellSkill::NbSpells] = {
        new SpellSkill( SpellSkill::FireBall, ABLE(eWizard), "Boule de feu", 4, "Lance une boule de feu sur l???ennemi", false, QPixmap(":/icons/skill/spell00.png"), QPixmap(":/icons/skill/spell01.png"), 20, 100, "D??g??ts" ),
        new SpellSkill( SpellSkill::HealingHalo, ABLE(eArcher)|ABLE(eWizard), "Halo de gu??rison", 4, "Vous soigne l??g??rement de vos blessures", false, QPixmap(":/icons/skill/spell10.png"), QPixmap(":/icons/skill/spell11.png"), 30, 30, "Soin" ),
        new SpellSkill( SpellSkill::Smoke, ABLE(eArcher)|ABLE(eWizard), "Nuage de fum??e", 4, "Permet de fuir un combat", false, QPixmap(":/icons/skill/spell20.png"), QPixmap(":/icons/skill/spell21.png"), 5, 100, "Taux de r??ussite" ),
        new SpellSkill( SpellSkill::PrimitiveShield, ABLE(eWizard), "Bouclier primitif", 4, "Augmente votre r??sistance pour le combat en cours", false, QPixmap(":/icons/skill/spell30.png"), QPixmap(":/icons/skill/spell31.png"), 20, 10, "R??sistance(%)" ),
        new SpellSkill( SpellSkill::DeathTouch, ABLE(eWizard), "Touch?? de la mort", 8, "Sort mortel pour l???ennemi mais avec peu de chance de r??ussite", false, QPixmap(":/icons/skill/spell40.png"), QPixmap(":/icons/skill/spell41.png"), 60, 25, "Taux de r??ussite" ),
        new SpellSkill( SpellSkill::Poisoning, ABLE(eWizard), "Empoisonnement", 7, "Sort d???empoisonnement qui fera des d??g??ts sur le long terme", false, QPixmap(":/icons/skill/spell50.png"), QPixmap(":/icons/skill/spell51.png"), 40, 80, "Taux de r??ussite" ),
        new SpellSkill( SpellSkill::Benediction, ABLE(eWizard), "B??n??diction", 5, "Sort permettant d???encaisser les trois prochaines attaques sans d??g??ts", false, QPixmap(":/icons/skill/spell60.png"), QPixmap(":/icons/skill/spell61.png"), 50, 3, "Tours d'invincibilit??" ),
        new SpellSkill( SpellSkill::Confusion, ABLE(eWizard), "Confusion", 10, "R??duit drastiquement le taux d???attaque de l???ennemi", false, QPixmap(":/icons/skill/spell70.png"), QPixmap(":/icons/skill/spell71.png"), 60, 70, "Taux de r??ussite" )
    };
};


class SwordMan : public Hero
{
    Q_OBJECT

public:
    SwordMan(QString);
    ~SwordMan();

public:
    int getHeroClass();

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:

    void serialize(QDataStream& stream)const
    {
        stream << mClass
               << mName
               << mMoveHandler.lastPos
               << mLife.curLife << mLife.maxLife
               << mMana.curMana << mMana.maxMana
               << mStamina.curStamina << mStamina.maxStamina
               << mCoin
               << mExperience.level << mExperience.points << mExperience.pointsToLevelUp
               << mSkillPoints;
        for(int i = 0; i < PassiveSkill::NbSkills; i++)
        {
            stream << mSkillList[i]->isUnlock();
        }
        for(int i = 0; i < SpellSkill::NbSpells; i++)
        {
            stream << mSpellList[i]->isUnlock();
        }
        mBag->serialize(stream);
        mGear->serialize(stream);

        qDebug() << "SERIALIZED[in]  : Swordman";
    }
    void deserialize(QDataStream& stream)
    {
        QPointF location(0,0);
        stream >> mName
               >> location
               >> mLife.curLife >> mLife.maxLife
               >> mMana.curMana >> mMana.maxMana
               >> mStamina.curStamina >> mStamina.maxStamina
               >> mCoin
               >> mExperience.level >> mExperience.points >> mExperience.pointsToLevelUp
               >> mSkillPoints;
        for(int i = 0; i < PassiveSkill::NbSkills; i++)
        {
            bool isUnlock = false;
            stream >> isUnlock;
            if(isUnlock)
                mSkillList[i]->unlockSkill();
        }
        for(int i = 0; i < SpellSkill::NbSpells; i++)
        {
            bool isUnlock = false;
            stream >> isUnlock;
            if(isUnlock)
                mSpellList[i]->unlockSkill();
        }
        mBag->deserialize(stream);
        mGear->deserialize(stream);

        setLocation(location);

        qDebug() << "SERIALIZED[out] : Swordman";
    }
};


class Archer : public Hero
{
    Q_OBJECT

public:
    Archer(QString);
    ~Archer();

public:
    int getHeroClass();

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:

    void serialize(QDataStream& stream)const
    {
        stream << mClass
               << mName
               << mMoveHandler.lastPos
               << mLife.curLife << mLife.maxLife
               << mMana.curMana << mMana.maxMana
               << mStamina.curStamina << mStamina.maxStamina
               << mCoin
               << mExperience.level << mExperience.points << mExperience.pointsToLevelUp
               << mSkillPoints;
        for(int i = 0; i < PassiveSkill::NbSkills; i++)
        {
            stream << mSkillList[i]->isUnlock();
        }
        for(int i = 0; i < SpellSkill::NbSpells; i++)
        {
            stream << mSpellList[i]->isUnlock();
        }
        mBag->serialize(stream);
        mGear->serialize(stream);

        qDebug() << "SERIALIZED[in]  : Archer";
    }
    void deserialize(QDataStream& stream)
    {
        QPointF location(0,0);
        stream >> mName
               >> location
               >> mLife.curLife >> mLife.maxLife
               >> mMana.curMana >> mMana.maxMana
               >> mStamina.curStamina >> mStamina.maxStamina
               >> mCoin
               >> mExperience.level >> mExperience.points >> mExperience.pointsToLevelUp
               >> mSkillPoints;
        for(int i = 0; i < PassiveSkill::NbSkills; i++)
        {
            bool isUnlock = false;
            stream >> isUnlock;
            if(isUnlock)
                mSkillList[i]->unlockSkill();
        }
        for(int i = 0; i < SpellSkill::NbSpells; i++)
        {
            bool isUnlock = false;
            stream >> isUnlock;
            if(isUnlock)
                mSpellList[i]->unlockSkill();
        }
        mBag->deserialize(stream);
        mGear->deserialize(stream);

        setLocation(location);

        qDebug() << "SERIALIZED[out] : Archer";
    }
};






class Wizard : public Hero
{
    Q_OBJECT

public:
    Wizard(QString);
    ~Wizard();

public:
    int getHeroClass();

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:

    void serialize(QDataStream& stream)const
    {
        stream << mClass
               << mName
               << mMoveHandler.lastPos
               << mLife.curLife << mLife.maxLife
               << mMana.curMana << mMana.maxMana
               << mStamina.curStamina << mStamina.maxStamina
               << mCoin
               << mExperience.level << mExperience.points << mExperience.pointsToLevelUp
               << mSkillPoints;
        for(int i = 0; i < PassiveSkill::NbSkills; i++)
        {
            stream << mSkillList[i]->isUnlock();
        }
        for(int i = 0; i < SpellSkill::NbSpells; i++)
        {
            stream << mSpellList[i]->isUnlock();
        }
        mBag->serialize(stream);
        mGear->serialize(stream);

        qDebug() << "SERIALIZED[in]  : Wizard";
    }
    void deserialize(QDataStream& stream)
    {
        QPointF location(0,0);
        stream >> mName
               >> location
               >> mLife.curLife >> mLife.maxLife
               >> mMana.curMana >> mMana.maxMana
               >> mStamina.curStamina >> mStamina.maxStamina
               >> mCoin
               >> mExperience.level >> mExperience.points >> mExperience.pointsToLevelUp
               >> mSkillPoints;
        for(int i = 0; i < PassiveSkill::NbSkills; i++)
        {
            bool isUnlock = false;
            stream >> isUnlock;
            if(isUnlock)
                mSkillList[i]->unlockSkill();
        }
        for(int i = 0; i < SpellSkill::NbSpells; i++)
        {
            bool isUnlock = false;
            stream >> isUnlock;
            if(isUnlock)
                mSpellList[i]->unlockSkill();
        }
        mBag->deserialize(stream);
        mGear->deserialize(stream);

        setLocation(location);

        qDebug() << "SERIALIZED[out] : Wizard";
    }
};


#endif // HERO_H
