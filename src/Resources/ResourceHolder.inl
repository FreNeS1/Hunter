template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> res(new Resource);
	if (!res->loadFromFile(filename))
	{
		std::stringstream ss;
		ss << "Failed to load resource at \"" << filename << "\"";
		utils::FileLogger::Log(utils::FileLogger::LogType::LOG_ERROR, ss.str().c_str());
	}
	else
		insertResource(id, std::move(res));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	std::unique_ptr<Resource> res(new Resource);
	if (!res->loadFromFile(filename, secondParam))
	{
		std::stringstream ss;
		ss << "Failed to load resource at \"" << filename << "\"";
		utils::FileLogger::Log(utils::FileLogger::LogType::LOG_ERROR, ss.str().c_str());
	}
	else
		insertResource(id, std::move(res));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = resourceMap.find(id);
	assert(found != resourceMap.end());		// When we ask for a resource we actually put in, there should NEVER be a missing one
	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = resourceMap.find(id);
	assert(found != resourceMap.end());		// When we ask for a resource we actually put in, there should NEVER be a missing one
	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
	auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);				// When manually inserting, the inserted should never be null
}