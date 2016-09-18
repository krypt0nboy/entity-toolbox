<?php

/**
 * Class ThemeBuilder
 */
class EntityThemeBuilder extends ThemeThemeBuilder {
  use EntityDependentTraits, EntityDependentBuilderTraits, EntityToolboxDependentTraits, EntityToolboxDependentBuilderTraits;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    parent::__construct($args);
    $this->alterStructure();
  }

  protected function initTemplateVars() {
    $flattened = $this->extractToolboxInfoTemplateVars();
    $this->setTemplateVars($flattened);
    parent::initTemplateVars();
  }

  /**
   *
   */
  protected function alterStructure() {
    $structure                              = &$this->structure;
    $structure['render element']['default'] = 'element';
    $structure['file']['default']           = NULL;
    $structure['path']['default']           = NULL;
    $structure['template']['default']       = 'src/templates/entities/%toolbox_info_entity_type%';
  }
}