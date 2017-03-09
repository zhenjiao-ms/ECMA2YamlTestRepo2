echo "Executing docfx merge command" | timestamp
$repositoryRoot = $ParameterDictionary.environment.repositoryRoot
$docfxExe = Join-Path $parameterDictionary.environment.packages["docfx.console"].packageRootFolder "tools/docfx.exe"

echo $ParameterDictionary.docset.docfxConfigFile
pushd (Join-Path $repositoryRoot $ParameterDictionary.environment.publishConfigContent.docsets_to_publish[0].build_source_folder)
& $docfxExe merge
if ($LASTEXITCODE -ne 0)
{
    popd
    exit $LASTEXITCODE
}
popd