#pragma once

#include <vector>

#include "Common.h"

class IGene
{
public:
    virtual IGene& Mutate() = 0;
    virtual IGene& set_random() = 0;
    virtual IGene* clone() const = 0;
};

class IGeneContainer
{
public:
    virtual uint32_t size() = 0;
    virtual void resize(uint32_t size) = 0;
    virtual void clear() = 0;
};

class IGenome
{
protected:
    IGeneContainer *gene_;
    uint32_t size_; // Number of bits

public:
    IGenome();
    IGenome(uint32_t size);
    IGenome(const IGenome &genome);
    virtual ~IGenome();

    uint32_t set_size(uint32_t size);
    inline uint32_t size() const { return size_; }

    inline IGene& set_gene(uint32_t i, IGene& value);
    virtual IGenome& Randomize();

    virtual inline IGene& set_random(uint32_t i);
    virtual IGene& gene(uint32_t i) = 0;
    virtual IGene& set_gene(uint32_t i, const IGene& value) = 0;
    virtual IGene& Mutate(uint32_t i) = 0;
    virtual IGene *RandomGeneFactory() = 0;
    virtual IGenome *clone() const = 0;
};

