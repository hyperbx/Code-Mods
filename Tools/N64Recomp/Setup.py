import sys, os, glob, requests, zipfile, tarfile
from tqdm import tqdm

work = os.path.dirname(os.path.abspath(__file__))
os.chdir(work)

def get_remote_platform_name(platform):
    platform_lower = platform.lower()

    if platform_lower.startswith("win"):
        return "Windows"
    elif platform_lower.startswith("mac"):
        return "Darwin"
    elif platform_lower.startswith("lin"):
        return "Linux"

    return platform

def get_remote_arch_name(platform, arch):
    platform_lower = platform.lower()

    if "arm" in arch.lower():
        if platform_lower.startswith("mac"):
            return "arm64"
    else:
        if platform_lower.startswith("win"):
            return "AMD64"
        else:
            return "x86_64"
    
    return arch

def get_release_assets(owner, repo, tag = None):
    if tag:
        url = f"https://api.github.com/repos/{owner}/{repo}/releases/tags/{tag}"
    else:
        url = f"https://api.github.com/repos/{owner}/{repo}/releases/latest"
    
    response = requests.get(url)
    response.raise_for_status()

    data = response.json()
    assets = data.get("assets", [])

    return [(asset["name"], asset["browser_download_url"]) for asset in assets]

def download_asset(src, dst):
    with requests.get(src, stream=True) as response:
        response.raise_for_status()

        total = int(response.headers.get("content-length", 0))
        progress = tqdm(desc = "Downloading", total = total, unit = "B", unit_scale = True, unit_divisor = 1024)

        with open(dst, "wb") as file, progress:
            for chunk in response.iter_content(8192):
                file.write(chunk)
                progress.update(len(chunk))
                
    return dst

def extract_asset(src, dst):
    os.makedirs(dst, exist_ok = True)

    with tqdm(desc = "Extracting", unit = "file") as progress:
        if src.endswith(".zip"):
            with zipfile.ZipFile(src, "r") as archive:
                files = archive.infolist()
                progress.total = len(files)

                for file in files:
                    archive.extract(file, dst)
                    progress.update(1)

        elif src.endswith(".tar.xz"):
            with tarfile.open(src, "r:xz") as archive:
                members = archive.getmembers()
                progress.total = len(members)

                for member in members:
                    archive.extract(member, dst, filter = "tar")
                    progress.update(1)

    return dst

def check_tools(path):
    return len(glob.glob(f"{path}/nrs_bin/clang*")) > 0

def get_tools(platform, arch, dst):
    assets = get_release_assets("LT-Schmiddy", "n64recomp-clang")
    assets_found = False

    remote_platform = get_remote_platform_name(platform)
    remote_arch = get_remote_arch_name(platform, arch)

    for name, url in assets:
        if not name.startswith(f"{remote_platform}-{remote_arch}-ClangEssentialsAndN64Recomp"):
            continue
        
        print("Downloading build tools...")

        assets_found = True
        path = download_asset(url, name)

        if not os.path.isfile(path):
            print("Failed to download build tools.")
            return -1
        
        os.makedirs(dst, exist_ok = True)
        extract_asset(path, dst)

        print("Cleaning up...")
        os.remove(path)
        
        break

    if not assets_found:
        print(f"No build tools available for {platform} ({arch}).")
        return -1
    
    return 0

def main():
    platform = "Windows"
    arch = "x64"
    force = False

    for i in range(len(sys.argv)):
        arg = sys.argv[i]
        if arg == "-f" or arg == "--force":
            force = True
        else:
            if i == 1:
                platform = arg
            elif i == 2:
                arch = arg
    
    tools = f"{platform}/{arch}"
    
    if not force and check_tools(tools):
        print("Build environment already set up, use -f|--force to redownload tools.")
        return 0
    
    print(f"Setting up build environment for {platform} ({arch})...")

    return get_tools(platform, arch, tools)

if __name__ == "__main__":
    result = main()
    sys.exit(result)
