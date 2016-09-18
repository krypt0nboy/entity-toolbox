<?php

/**
 * Class EntityToolboxDependentBuilderTraits
 */
trait EntityToolboxDependentBuilderTraits {

  /**
   * Extracts the info from toolbox_info.
   *
   * @return array
   */
  public function extractToolboxInfoTemplateVars() {
    $vars = $this->extractTemplateVars($this->toolboxInfo, '', 'toolbox_info_');
    $vars += array('toolbox_info_entity_type' => $this->entityType);
    $vars += array(
      'toolbox_info_module_path' =>
        drupal_get_path('module', $this->toolboxInfo['module'])
    );

    return $vars;
  }
}