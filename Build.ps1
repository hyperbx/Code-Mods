param
(
    [Switch]$Archive,
    [String]$BlockList,
    [Switch]$Clean,
    [String]$Configuration = "Release",
    [Switch]$Help
)

$work = $pwd
$blockList = $BlockList.Split(";");
$artifactsDir = [System.IO.Directory]::CreateDirectory([System.IO.Path]::Combine($work, "Artifacts"))

if ($Help)
{
    Write-Host "Code Mods Build Script"
    Write-Host
    Write-Host "Parameters:"
    Write-Host "-Archive - archives the build artifacts."
    Write-Host "-BlockList - semi-colon separated list of projects not to build."
    Write-Host "-Clean - clean the projects before building."
    Write-Host "-Configuration [name] - build with a specific configuration."
    Write-Host "-Help - display help."
    exit
}

$vs = ./Tools/vswhere.exe -nologo -latest -prerelease -property installationPath
$vsCommonTools = [System.IO.Path]::Combine($vs, "Common7", "Tools")

pushd $vsCommonTools
    cmd /c "VsDevCmd.bat > nul 2> nul &set" |
    foreach {
        if ($_ -match "=") {
            $v = $_.split("=", 2)
            Set-Item -Force -Path "ENV:\$($v[0])" -Value "$($v[1])" 
        }
    }
popd

function GetProjectProperty([String]$in_projectPath, [String]$in_propertyName)
{
    return & msbuild /NoLogo /p:Configuration="${Configuration}" -getProperty:"${in_propertyName}" "${in_projectPath}"
}

function IsDependency([String]$in_path)
{
    return $in_path.Contains("Dependencies")
}

function BuildSolutions([String]$in_root)
{
    $root = [System.IO.Path]::Combine($work, $in_root)

    foreach ($solutionPath in [System.IO.Directory]::EnumerateFiles($root, "*.sln", [System.IO.SearchOption]::AllDirectories))
    {
        if (IsDependency($solutionPath))
        {
            continue
        }
        
        $solutionDir  = Split-Path $solutionPath
        $solutionName = [System.IO.Path]::GetFileNameWithoutExtension($solutionPath)
        
        if ($blockList.Contains($solutionName))
        {
            continue
        }

        $target = "Build"

        if ($Clean)
        {
            $target = "Clean;" + $target
        }

        Write-Host
        Write-Host ("**************" + '*' * $solutionPath.Length) -ForegroundColor DarkGreen
        Write-Host "* Solution: ${solutionPath} *"                 -ForegroundColor DarkGreen
        Write-Host ("**************" + '*' * $solutionPath.Length) -ForegroundColor DarkGreen

        & msbuild /NoLogo /v:m /t:"${target}" /Restore /p:RestorePackagesConfig=true /p:Configuration="${Configuration}" "${solutionPath}"

        if ($Archive)
        {
            $projects = dotnet sln "${solutionPath}" list |
                Select-Object -Skip 2 |
                ForEach-Object {
                    Join-Path $solutionDir $_.Trim()
                }

            foreach ($projectPath in $projects)
            {
                $projectDir  = GetProjectProperty $projectPath "ProjectDir"
                $projectName = (GetProjectProperty $projectPath "ProjectName").Replace(" ", "")
                $binDir      = [System.IO.Path]::Combine($projectDir, "bin")

                foreach ($platformDir in [System.IO.Directory]::EnumerateDirectories($binDir))
                {
                    $platformName = [System.IO.Path]::GetFileName($platformDir)

                    if ($platformName -eq $Configuration)
                    {
                        # Required for some .NET projects.
                        $targetDir = $platformDir
                        $targetName = "${projectName}-${Configuration}.zip"
                    }
                    else
                    {
                        $targetDir = [System.IO.Path]::Combine($platformDir, $Configuration)
                        $targetName = "${projectName}-${platformName}-${Configuration}.zip"
                    }

                    if (![System.IO.Directory]::Exists($targetDir))
                    {
                        Write-Host
                        Write-Host ("***********************" + '*' * $targetDir.Length) -ForegroundColor DarkRed
                        Write-Host "* Cannot archive project binaries."                  -ForegroundColor DarkRed
                        Write-Host "* Directory not found: ${targetDir}"                 -ForegroundColor DarkRed
                        Write-Host ("***********************" + '*' * $targetDir.Length) -ForegroundColor DarkRed
                        exit -1
                    }

                    $artifactRootDir    = [System.IO.Directory]::CreateDirectory([System.IO.Path]::Combine($artifactsDir.FullName, $in_root, $solutionName))
                    $artifactTargetPath = [System.IO.Path]::Combine($artifactRootDir.FullName, $targetName)

                    cd $targetDir
                    Compress-Archive -Force * $artifactTargetPath
                    cd $work
                }
            }
        }
    }
}

function BuildMakefiles([String]$in_root)
{
    $root = [System.IO.Path]::Combine($work, $in_root)

    foreach ($makefilePath in [System.IO.Directory]::EnumerateFiles($root, "Makefile", [System.IO.SearchOption]::AllDirectories))
    {
        if (IsDependency($makefilePath))
        {
            continue
        }

        $makefileDir = Split-Path $makefilePath
        $projectName = [System.IO.Path]::GetFileName($makefileDir)
        
        if ($blockList.Contains($projectName))
        {
            continue
        }

        $args = @()

        if ($Clean)
        {
            $args += "clean"
        }

        $args += "all"

        Write-Host
        Write-Host ("**************" + '*' * $makefilePath.Length) -ForegroundColor DarkGreen
        Write-Host "* Makefile: ${makefilePath} *"                 -ForegroundColor DarkGreen
        Write-Host ("**************" + '*' * $makefilePath.Length) -ForegroundColor DarkGreen

        & make -C "${makefileDir}" @args

        if ($Archive)
        {
            $projectNameSafe = $projectName.Replace(" ", "")
            $binDir = [System.IO.Path]::Combine($makefileDir, "bin")
            $targetName = "${projectNameSafe}-${Configuration}.zip"
            
            if (![System.IO.Directory]::Exists($binDir))
            {
                Write-Host
                Write-Host ("***********************" + '*' * $binDir.Length) -ForegroundColor DarkRed
                Write-Host "* Cannot archive project binaries."               -ForegroundColor DarkRed
                Write-Host "* Directory not found: ${binDir}"                 -ForegroundColor DarkRed
                Write-Host ("***********************" + '*' * $binDir.Length) -ForegroundColor DarkRed
                exit -1
            }
            
            $artifactRootDir    = [System.IO.Directory]::CreateDirectory([System.IO.Path]::Combine($artifactsDir.FullName, $in_root))
            $artifactTargetPath = [System.IO.Path]::Combine($artifactRootDir.FullName, $targetName)

            cd $binDir
            Compress-Archive -Force * $artifactTargetPath
            cd $work
        }
    }
}

BuildSolutions("Games")
BuildMakefiles("Games/Zelda 64 Recompiled/Majora's Mask")
