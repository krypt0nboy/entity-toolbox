<?php

/**
 * Class ModuleDependentBuilderTraits
 */
trait ModuleDependentBuilderTraits {
  /**
   * Extracts the info from module info.
   *
   * @return array
   */
  public function extractModuleInfoTemplateVars() {
    $flattened = $this->extractTemplateVars($this->moduleInfo, '', 'module_info_');
    $flattened += array(
      'module_info_module_path' =>
        drupal_get_path('module', $this->module)
    );

    return $flattened;
  }
}