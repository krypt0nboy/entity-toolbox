<?php

/**
 * Class RelationDrupalSchemaFieldsBuilder
 */
class RelationDrupalSchemaFieldsBuilder extends DrupalSchemaFieldsBuilder {
  use PropertyDependentTraits, ReferenceDependentTraits, ReferenceDependentBuilderTraits, PropertyDependentBuilderTraits;

  /** {{@inheritdoc}} */
  protected function initTemplateVars(array $vars = array()) {
    $vars += $this->extractReferenceInfoTemplateVars();
    parent::initTemplateVars($vars);
  }

  /**
   * Evaluates if a property is the property for which the table is built.
   *
   * @param string $propertyName
   *   The property name.
   *
   * @return bool
   */
  public function isSchemaRelationProperty($propertyName) {
    return $this->propertyName == $propertyName;
  }

  /** {{@inheritdoc}} */
  protected function evalExtractPropertyFieldMethods($propertyName, $schemaType = NULL) {
    $eval              = array();
    $helper            = $this->getPropsHelper();
    $eval['required']  = $this->isSchemaRelationProperty($propertyName) || $helper->propIsRequiredForSchema($propertyName);
    $eval['has_field'] = $helper->propHasSchemaFieldName($propertyName, $schemaType);

    return $eval;
  }

  /** {{@inheritdoc}} */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'property_name'  => $this->propertyName,
      'reference'      => $this->reference,
      'reference_info' => $this->referenceInfo,
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}