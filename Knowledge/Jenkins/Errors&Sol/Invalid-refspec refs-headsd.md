# Problem logs 
:GitHub pull request #1 of commit a69bf1352d9bce0868ea4a7fb1d368d96694f300, no merge conflicts.
Setting status of a69bf1352d9bce0868ea4a7fb1d368d96694f300 to PENDING with url https://f61a-41-33-250-194.ngrok-free.app/job/Building_Pipeline/1/ and message: 'Build started for merge commit.'
java.lang.IllegalArgumentException: Invalid refspec refs/heads/**
    at PluginClassLoader for git-client//org.eclipse.jgit.transport.RefSpec.checkValid(RefSpec.java:599)
    at PluginClassLoader for git-client//org.eclipse.jgit.transport.RefSpec.<init>(RefSpec.java:203)
    at PluginClassLoader for git-client//org.eclipse.jgit.transport.RefSpec.<init>(RefSpec.java:255)
    at PluginClassLoader for git//jenkins.plugins.git.GitSCMFileSystem$BuilderImpl.build(GitSCMFileSystem.java:404)
    at PluginClassLoader for scm-api//jenkins.scm.api.SCMFileSystem.of(SCMFileSystem.java:219)
    at PluginClassLoader for workflow-cps//org.jenkinsci.plugins.workflow.cps.CpsScmFlowDefinition.create(CpsScmFlowDefinition.java:126)
    at PluginClassLoader for workflow-cps//org.jenkinsci.plugins.workflow.cps.CpsScmFlowDefinition.create(CpsScmFlowDefinition.java:73)
    at PluginClassLoader for workflow-job//org.jenkinsci.plugins.workflow.job.WorkflowRun.run(WorkflowRun.java:311)
    at hudson.model.ResourceController.execute(ResourceController.java:101)
    at hudson.model.Executor.run(Executor.java:446)
Setting status of a69bf1352d9bce0868ea4a7fb1d368d96694f300 to FAILURE with url https://f61a-41-33-250-194.ngrok-free.app/job/Building_Pipeline/1/ and message: 'Build finished. '
Finished: FAILURE

# The Solution :
Disable the lightweight checkout & specify the branch to be built , don't leave it blank
