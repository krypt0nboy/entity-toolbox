<?php

/**
 * Class EntityToolboxInfoReferencePropertySchemasFieldsNameBuilder
 */
class EntityToolboxInfoReferencePropertySchemasFieldsNameBuilder extends EntityToolboxInfoPropertySchemasFieldsNameBuilder {
  use ReferenceDependentTraits, ReferenceDependentBuilderTraits;

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->extractReferenceInfoTemplateVars();
    parent::initTemplateVars($vars);
  }
}