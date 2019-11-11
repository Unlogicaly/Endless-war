

std::string define_landscape_type(const std::string &s)
{
    for (auto type : landscape)
    {
        for (auto &sub : type.second)
            if (sub.first == s)
                return type.first;
    }
    throw std::runtime_error("Wrong landscape name");
}

std::string define_terrain_type(const std::string &s)
{
    for (auto type : terrain)
    {
        for (auto &sub : type.second)
            if (sub.first == s)
                return type.first;
    }
    throw std::runtime_error("Wrong terrain name");
}
