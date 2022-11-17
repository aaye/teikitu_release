function Choco-Install {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory)]
        [string] $PackageName,
        [string[]] $ArgumentList,
        [int] $RetryCount = 5
    )

    process {
        $count = 1
        while($true)
        {
            Write-Host "Running [#$count]: choco install $packageName -y $argumentList"
            choco install $packageName -y @argumentList --no-progress

            $pkg = choco list --localonly $packageName --exact --all --limitoutput
            if ($pkg) {
                Write-Host "Package installed: $pkg"
                break
            }
            else {
                $count++
                if ($count -ge $retryCount) {
                    Write-Host "Could not install $packageName after $count attempts"
                    exit 1
                }
                Start-Sleep -Seconds 30
            }
        }
    }
}

Choco-Install circleci-cli
Choco-Install cmake
Choco-Install ninja
Choco-Install llvm
Choco-Install winflexbison
Choco-Install python3

pip3 install jinja2
pip3 install PyOpenGL
pip3 install pyside6==6.5.1.1 --ignore-installed

git config --global user.email "andrew.aye@gmail.com"
git config --global user.name "Andrew Aye"
