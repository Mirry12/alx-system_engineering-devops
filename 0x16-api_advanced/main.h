import requests

def number_of_subscribers(subreddit: str) -> int:
    """Return the number of subscribers for a given subreddit, or 0 if invalid."""
    url = f"https://www.reddit.com/r/{subreddit}/about.json"
    headers = {'User-Agent': 'Mozilla/5.0'}
    response = requests.get(url, headers=headers)
    if response.status_code == 200:
        data = response.json()
        return data.get('data', {}).get('subscribers', 0)
    return 0

def top_ten(subreddit: str) -> None:
    """Print the titles of the top 10 hottest posts from a subreddit, or None if invalid."""
    url = f"https://www.reddit.com/r/{subreddit}/hot.json?limit=10"
    headers = {'User-Agent': 'Mozilla/5.0'}
    response = requests.get(url, headers=headers)
    if response.status_code == 200:
        data = response.json()
        posts = data.get('data', {}).get('children', [])
        if posts:
            for post in posts:
                print(post.get('data', {}).get('title'))
        else:
            print(None)
    else:
        print(None)

def recurse(subreddit: str, hot_list: list = None) -> list:
    """Recursively gather hot posts from a subreddit."""
    if hot_list is None:
        hot_list = []

    url = f"https://www.reddit.com/r/{subreddit}/hot.json"
    headers = {'User-Agent': 'Mozilla/5.0'}
    response = requests.get(url, headers=headers)
    if response.status_code == 200:
        data = response.json()
        posts = data.get('data', {}).get('children', [])
        after = data.get('data', {}).get('after', None)
        
        for post in posts:
            hot_list.append(post.get('data', {}).get('title'))

        # Check if there's more to fetch
        if after:
            recurse(subreddit, hot_list=hot_list)
        else:
            return hot_list
    else:
        return hot_list
