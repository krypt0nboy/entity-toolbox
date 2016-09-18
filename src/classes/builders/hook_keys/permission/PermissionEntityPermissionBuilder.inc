<?php

/**
 * Class PermissionEntityPermissionBuilder
 */
class PermissionEntityPermissionBuilder extends PermissionPermissionBuilder {
  use EntityDependentTraits, EntityToolboxDependentTraits, EntityToolboxDependentBuilderTraits;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'model_class' => 'PermissionPermissionModel'
    ), $args);
    parent::__construct($args);
  }

  protected function initTemplateVars() {
    $flattened = $this->extractToolboxInfoTemplateVars();
    $this->templateVars += $flattened;
  }

}