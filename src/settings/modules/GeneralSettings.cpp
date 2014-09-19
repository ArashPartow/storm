#include "src/settings/modules/GeneralSettings.h"

#include "src/settings/SettingsManager.h"

namespace storm {
    namespace settings {
        namespace modules {
            
            const std::string GeneralSettings::moduleName = "general";
            const std::string GeneralSettings::helpOptionName = "help";
            const std::string GeneralSettings::helpOptionShortName = "h";
            const std::string GeneralSettings::verboseOptionName = "verbose";
            const std::string GeneralSettings::verboseOptionShortName = "v";
            const std::string GeneralSettings::exportDotOptionName = "exportdot";
            const std::string GeneralSettings::configOptionName = "config";
            const std::string GeneralSettings::configOptionShortName = "c";
            const std::string GeneralSettings::explicitOptionName = "explicit";
            const std::string GeneralSettings::explicitOptionShortName = "e";
            const std::string GeneralSettings::symbolicOptionName = "symbolic";
            const std::string GeneralSettings::symbolicOptionShortName = "s";
            const std::string GeneralSettings::pctlOptionName = "pctl";
            const std::string GeneralSettings::cslOptionName = "csl";
            const std::string GeneralSettings::ltlOptionName = "ltl";
            const std::string GeneralSettings::transitionRewardsOptionName = "transrew";
            const std::string GeneralSettings::stateRewardsOptionName = "staterew";
            const std::string GeneralSettings::counterexampleOptionName = "counterexample";
            const std::string GeneralSettings::fixDeadlockOptionName = "fixDeadlocks";
            const std::string GeneralSettings::fixDeadlockOptionShortName = "fix";
            const std::string GeneralSettings::timeoutOptionName = "timeout";
            const std::string GeneralSettings::timeoutOptionShortName = "t";
            const std::string GeneralSettings::eqSolverOptionName = "eqsolver";
            const std::string GeneralSettings::lpSolverOptionName = "lpsolver";
            const std::string GeneralSettings::constantsOptionName = "constants";
            const std::string GeneralSettings::constantsOptionShortName = "const";
            
            GeneralSettings::GeneralSettings(storm::settings::SettingsManager& settingsManager) : ModuleSettings(settingsManager) {
                // First, we need to create all options of this module.
                std::vector<std::shared_ptr<Option>> options;
                options.push_back(storm::settings::OptionBuilder(moduleName, helpOptionName, helpOptionShortName, "Shows all available options, arguments and descriptions.").build());
                options.push_back(storm::settings::OptionBuilder(moduleName, verboseOptionName, verboseOptionShortName, "Enables more verbose output.").build());
                options.push_back(storm::settings::OptionBuilder(moduleName, exportDotOptionName, "", "If given, the loaded model will be written to the specified file in the dot format.")
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("filename", "The name of the file to which the model is to be written.").build()).build());
                options.push_back(storm::settings::OptionBuilder(moduleName, configOptionName, configOptionShortName, "If given, this file will be read and parsed for additional configuration settings.")
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("filename", "The name of the file from which to read the configuration.").addValidationFunctionString(storm::settings::ArgumentValidators::existingReadableFileValidator()).build()).build());
                options.push_back(storm::settings::OptionBuilder(moduleName, explicitOptionName, explicitOptionShortName, "Parses the model given in an explicit (sparse) representation.")
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("filename", "The name of the file from which to read the transitions.").addValidationFunctionString(storm::settings::ArgumentValidators::existingReadableFileValidator()).build())
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("filename", "The name of the file from which to read the state labeling.").addValidationFunctionString(storm::settings::ArgumentValidators::existingReadableFileValidator()).build()).build());
                options.push_back(storm::settings::OptionBuilder(moduleName, symbolicOptionName, symbolicOptionShortName, "Parses the model given in a symbolic representation.")
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("filename", "The name of the file from which to read the symbolic model.").addValidationFunctionString(storm::settings::ArgumentValidators::existingReadableFileValidator()).build()).build());
                options.push_back(storm::settings::OptionBuilder(moduleName, pctlOptionName, "", "Specifies the PCTL formulas that are to be checked on the model.")
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("filename", "The file from which to read the PCTL formulas.").addValidationFunctionString(storm::settings::ArgumentValidators::existingReadableFileValidator()).build()).build());
                options.push_back(storm::settings::OptionBuilder(moduleName, cslOptionName, "", "Specifies the CSL formulas that are to be checked on the model.")
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("filename", "The file from which to read the CSL formulas.").addValidationFunctionString(storm::settings::ArgumentValidators::existingReadableFileValidator()).build()).build());
                options.push_back(storm::settings::OptionBuilder(moduleName, ltlOptionName, "", "Specifies the LTL formulas that are to be checked on the model.")
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("filename", "The file from which to read the LTL formulas.").addValidationFunctionString(storm::settings::ArgumentValidators::existingReadableFileValidator()).build()).build());
                options.push_back(storm::settings::OptionBuilder(moduleName, counterexampleOptionName, "", "Generates a counterexample for the given PRCTL formulas if not satisfied by the model")
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("filename", "The name of the file to which the counterexample is to be written.").build()).build());
                
                options.push_back(storm::settings::OptionBuilder(moduleName, transitionRewardsOptionName, "", "If given, the transition rewards are read from this file and added to the explicit model. Note that this requires the model to be given as an explicit model (i.e., via --" + explicitOptionName + ").")
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("filename", "The file from which to read the transition rewards.").addValidationFunctionString(storm::settings::ArgumentValidators::existingReadableFileValidator()).build()).build());
                options.push_back(storm::settings::OptionBuilder(moduleName, stateRewardsOptionName, "", "If given, the state rewards are read from this file and added to the explicit model. Note that this requires the model to be given as an explicit model (i.e., via --" + explicitOptionName + ").");
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("filename", "The file from which to read the state rewards.").addValidationFunctionString(storm::settings::ArgumentValidators::existingReadableFileValidator()).build()).build());
                options.push_back(storm::settings::OptionBuilder(moduleName, fixDeadlockOptionName, fixDeadlockOptionShortName, "If the model contains deadlock states, they need to be fixed by setting this option.").build());
                
                std::vector<std::string> linearEquationSolver;
                linearEquationSolver.push_back("gmm++");
                linearEquationSolver.push_back("native");
                settingsManager.addOption();
                options.push_back(storm::settings::OptionBuilder(moduleName, eqSolverOptionName, "", "Sets which solver is preferred for solving systems of linear equations.")
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("name", "The name of the solver to prefer. Available are: gmm++ and native.").addValidationFunctionString(storm::settings::ArgumentValidators::stringInListValidator(linearEquationSolver)).setDefaultValueString("gmm++").build()).build());
                options.push_back(storm::settings::OptionBuilder(moduleName, timeoutOptionName, timeoutOptionShortName, "If given, computation will abort after the timeout has been reached.")
                                  .addArgument(storm::settings::ArgumentBuilder::createUnsignedIntegerArgument("time", "The number of seconds after which to timeout.").setDefaultValueUnsignedInteger(0).build()).build());

                std::vector<std::string> lpSolvers;
                lpSolvers.push_back("gurobi");
                lpSolvers.push_back("glpk");
                settingsManager.addOption();
                options.push_back(storm::settings::OptionBuilder(moduleName, lpSolverOptionName, "", "Sets which LP solver is preferred.")
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("name", "The name of an LP solver. Available are: gurobi and glpk.").addValidationFunctionString(storm::settings::ArgumentValidators::stringInListValidator(lpSolvers)).setDefaultValueString("glpk").build()).build());
                options.push_back(storm::settings::OptionBuilder(moduleName, constantsOptionName, constantsOptionShortName, "Specifies the constant replacements to use in symbolic models. Note that Note that this requires the model to be given as an symbolic model (i.e., via --" + symbolicOptionName + ").")
                                  .addArgument(storm::settings::ArgumentBuilder::createStringArgument("values", "A comma separated list of constants and their value, e.g. a=1,b=2,c=3.").setDefaultValueString("").build()).build());
                
                // Finally, register all options that we just created.
                settingsManager.registerModule(moduleName, options);
            }
            
        } // namespace modules
    } // namespace settings
} // namespace storm